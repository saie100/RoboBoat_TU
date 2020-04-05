#include <SPI.h>
#include <RH_RF95.h>
#include <string.h>
#include <stdio.h> 
#include <math.h> 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* for Feather32u4 RFM9x */
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

#define SIZE_radiopacket 50

  /* The duration of time that the radio will wait to receive a packet */
#define RX_TIMEOUT_MS     1000

  /* The number of consequitive dropped packets that signify a disconnect event */
#define RF_DROP_PACKET_DISCONNECT   3 

volatile unsigned long missCnt = 0;

  /* Message that indicates a non-emergency state sent by the transmitter */
char okMsg[] = "TempleBoatNormal";
char batReading[20];

  /* Holds the current status of the emergency state as determined by the remote kill-switch */
volatile byte EmergencyState_RF = true;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /* This pin is the pin that the physical emergency switches are connected to */
#define PIN_EMERGENCY_SWITCH  1 
    /* if HIGH -> Emergency State
       if LOW -> Normal State (Manual or Autonomous)  */

  /* Holds the current status of the emergency state as determined by the onboard kill-switches */
volatile byte EmergencyState_SW = true; 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Relay Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  /* Calculates the net emergency state given radio and button state */
#define EMERGENCY_STATE   EmergencyState_SW || EmergencyState_RF
//volatile byte EmergencyState = true;

  /* These are the pins that the relay control signals are connected to */
#define PIN_MOTOR_RELAY       18
#define PIN_AMBER_LIGHT       19
#define PIN_RED_LIGHT         20
#define PIN_BLUE_LIGHT        21

  /* These are the values to turn ON the corresponding relay devices */
#define ON_MOTOR              LOW
#define ON_RED                HIGH
#define ON_BLUE               LOW
#define ON_AMBER              LOW

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ State Select Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /* This is the pin that is connected to the Raspberry Pi 4 that determines indicated if we are in the 
     manual control or autonomous control state so the lights can be selected accordingly */
#define PIN_CONTROL_SELECT    13
    /* if HIGH -> Manual Control (AMBER)
       if LOW -> Automous Control (BLUE)  */

// ======================================Battery Monitor Setup=====================================================
#define VBATPIN              A9
#define CHRG_V               4.2
#define EMPT_V               3.0

void setup()
{
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Digital I/O Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // configure the pin that congrols the main motor relays to output 
  pinMode(PIN_MOTOR_RELAY, OUTPUT); 

  // Configure the pin that controls the LEDs to output
  pinMode(PIN_RED_LIGHT, OUTPUT);
  pinMode(PIN_BLUE_LIGHT, OUTPUT);
  pinMode(PIN_AMBER_LIGHT, OUTPUT);

  // Configure the pin that controls the manual/autonomous select to input
  pinMode(PIN_CONTROL_SELECT, INPUT_PULLUP); // Use the internal pullup resistor

  // Configure the pin that will be connected to the onboard kill-switches to be input
  pinMode(PIN_EMERGENCY_SWITCH, INPUT); // Pullup resistor soldered onto the board

  stateHandler(); // Call the state handler to put the system into the emergency state from the start

  // Read the value of the onboard kill-switch pin
  EmergencyState_SW = digitalRead(PIN_EMERGENCY_SWITCH);

  // Configure the pin-change interrupt handler for the onboard kill-switches 
  attachInterrupt(digitalPinToInterrupt(PIN_EMERGENCY_SWITCH), ISR_EmergencyStateChange, CHANGE);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Serial Monitor Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Serial.begin(9600);
  delay(500);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  pinMode(RFM95_RST, OUTPUT);
  /* Manual reset of the radio */
  digitalWrite(RFM95_RST, HIGH); delay(100);
  digitalWrite(RFM95_RST, LOW);  delay(10);
  digitalWrite(RFM95_RST, HIGH); delay(10);

  while (!rf95.init()) Serial.println("LoRa radio init failed");
  Serial.println("LoRa radio init OK!");

  if (!rf95.setFrequency(RF95_FREQ)) Serial.println("setFrequency failed");
  else Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  rf95.setTxPower(23, false);
}

// =====================================================================================================
void loop()
{
  if (rf95.waitAvailableTimeout(RX_TIMEOUT_MS)) { // will execute if message is recieved before timeout
    if (rf95.available()) {   // Will execute if the radio is able to give us the received message
      radioAvailableExecute();
    }
    else {    // Will execute if the radio is not available
      missCnt++;    // Increment the miss count to track the failed-recieves
      Serial.println("Radio not available");
    }
  }
  else {    // Will execute if the radio times-out
    missCnt++;    // Increment the miss count to track the failed-recieves
    Serial.print("Radio timeout");
  }

  if (missCnt >= RF_DROP_PACKET_DISCONNECT)  // If three packets are missed in a row, we are now in the emergency state
    EmergencyState_RF = true;

  itoa(100*measureBattery()/4.2, batReading, 10);
  Serial.println(batReading);
  
  stateHandler();   // Call the state handler to update the lights and motor relays
}

// ====================================================================================================
void stateHandler() {
  if (EMERGENCY_STATE) {    // Will be executed if we are in emergency tate
    digitalWrite(PIN_MOTOR_RELAY, !ON_MOTOR);
    digitalWrite(PIN_RED_LIGHT, ON_RED);
    digitalWrite(PIN_BLUE_LIGHT, !ON_BLUE);
    digitalWrite(PIN_AMBER_LIGHT, !ON_AMBER);
  }
  else {    // Will be executed if we are NOT in the emergency state
    digitalWrite(PIN_MOTOR_RELAY, ON_MOTOR);
    digitalWrite(PIN_RED_LIGHT, !ON_RED);
    
    if (digitalRead(PIN_CONTROL_SELECT) == HIGH) {    // If in manual control mode
      digitalWrite(PIN_BLUE_LIGHT, ON_BLUE);
      digitalWrite(PIN_AMBER_LIGHT, !ON_AMBER);
    }
    else {    // If in autonomous control mode
      digitalWrite(PIN_BLUE_LIGHT, !ON_BLUE);
      digitalWrite(PIN_AMBER_LIGHT, ON_AMBER);
    }
  }
}

// =====================================================================================================
void radioAvailableExecute() {
  // Should be a message for us now
  uint8_t buf[SIZE_radiopacket];
  uint8_t len = sizeof(buf);

  if (rf95.recv(buf, &len)) {
    missCnt = 0; /* Reset the miss count if message received */
    RH_RF95::printBuffer("Received: ", buf, len);

    /* Compare the recieved and the known OK string */
    int ii;
    for (ii = 0; (okMsg[ii] == (char)buf[ii] && ((char)buf[ii] != '\0')); ii++);
    /* The emergency state is set if the received string does not match the OK string */
    int NormalMessage = (((char)buf[ii] == '\0') && (okMsg[ii] == '\0')); // This is non-zero during normal operation

    if (NormalMessage) 
      EmergencyState_RF = false; // Set EmergencyState_RF to FALSE if the recived message indicates normal operation
    else 
      EmergencyState_RF = true; // Set EmergencyState_RF to TRUE if the recived message indicates emergency operation

    Serial.print("RSSI: "); Serial.println(rf95.lastRssi(), DEC);
    /*
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~Detect Low Battery~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      float batPercent = (measureBattery()-EMPT_V) / (CHRG_V-EMPT_V);
      if (batPercent > 1) batPercent = 1;
      if (batPercent < 0.1){
      rf95.send("Rx<10%", sizeof("Rx<10%"));
      rf95.waitPacketSent();
      }
      else{
      rf95.send(buf, sizeof(buf));
      rf95.waitPacketSent();
      }
    */
    strcat(buf, " ");
    float batPercent = 100*(measureBattery()-EMPT_V) / (CHRG_V-EMPT_V);
    if (batPercent > 100) batPercent = 100;
    itoa(batPercent, batReading, 10);
    strcat(buf, batReading);
    Serial.println(batReading);
    
    rf95.send(buf, sizeof(buf));    // Send a response to the transmitter
    rf95.waitPacketSent();  // Wait until the packet has been sent before continuing
  }
  else { /* if receive fails */
    missCnt++;
    Serial.println("Receive failed");
  }
}

// =========================================Baterry Measurement=========================================
float measureBattery() {
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  return measuredvbat;
}

//==================On-Boat Button=============================================
void ISR_EmergencyStateChange(void) {
  if (EmergencyState_SW != digitalRead(PIN_EMERGENCY_SWITCH)) {
    delayMicroseconds(10000);
    if (EmergencyState_SW != digitalRead(PIN_EMERGENCY_SWITCH)) {
      EmergencyState_SW = !EmergencyState_SW;
    }
  }
}

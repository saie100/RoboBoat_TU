#include <Adafruit_SleepyDog.h> // Adds watchdog timer that will reset the transmitter if it stops for 10 seconds
#include <RH_RF95.h>
#include <SPI.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define WATCHDOG_TIMEOUT 10000 // Time of inactivity before restarting the arduino

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RFM95_RST 4 // The reset pin for the radio
#define RFM95_INT 7 // Slave select pin for the radio
#define RFM95_CS 8  // Chip select pin for the radio

#define RF95_FREQ 915.0   // Operating frequency of emergency receiver

RH_RF95 rf95(RFM95_CS, RFM95_INT); // Singleton instance of the radio driver

#define SIZE_radiopacket 50 // Max size of transmission
uint8_t buf[SIZE_radiopacket]; // Input buffer for the radio - declared globally to keep out of the stack
uint8_t len; // Holds the actual size of th received message

// The duration of time that the radio will wait to receive a packet
#define RF_TIMEOUT_MS     1000

// The number of consequitive dropped packets that signify a disconnect event
#define RF_DROP_PACKET_DISCONNECT   3

volatile unsigned int missCnt = 0; // Holds the current count of consequitive failed transmissions

char okMsg[] = "TempleBoatNormal"; // Message that indicates a non-emergency state sent by the transmitter
char batReading[20]; // Holds the battery Reading
char rssiReading[20]; // Holds the RSSI
char switchReading[20]; // Holds the switch Value

// Holds the current status of the emergency state as determined by the remote kill-switch
volatile byte EmergencyState_RF = true;

int ii;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This pin is the pin that the physical emergency switches are connected to
#define PIN_EMERGENCY_SWITCH  1
/* if HIGH -> Emergency State
   if LOW -> Normal State (Manual or Autonomous)  */

// Holds the current status of the emergency state as determined by the onboard kill-switches
volatile byte EmergencyState_SW = true;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Relay Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Calculates the net emergency state given radio and button state
#define EMERGENCY_STATE   EmergencyState_SW || EmergencyState_RF
//volatile byte EmergencyState = true;

// These are the pins that the relay control signals are connected to
#define PIN_MOTOR_RELAY       18
#define PIN_AMBER_LIGHT       19
#define PIN_RED_LIGHT         20
#define PIN_BLUE_LIGHT        21

// These are the values to turn ON the corresponding relay devices
#define ON_MOTOR              LOW
#define ON_RED                HIGH
#define ON_BLUE               LOW
#define ON_AMBER              LOW

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ State Select Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This is the pin that is connected to the Raspberry Pi 4 that determines indicated if we are in the
// manual control or autonomous control state so the lights can be selected accordingly
#define PIN_CONTROL_SELECT    13
// if HIGH -> Manual Control (AMBER)
// if LOW -> Automous Control (BLUE)

// ======================================Battery Monitor Setup=====================================================
#define VBATPIN A9  // The analog pin connected to the battery
#define CHRG_V 4.2  // The changed voltage of the batter
#define EMPT_V 3.0  // The discharged voltage of the battery
float measuredvbat;
unsigned char percent;

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
  //  attachInterrupt(digitalPinToInterrupt(PIN_EMERGENCY_SWITCH), ISR_EmergencyStateChange, CHANGE);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Serial Monitor Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //Serial.begin(9600);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Manual reset of the radio
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH); delay(100);
  digitalWrite(RFM95_RST, LOW);  delay(10);
  digitalWrite(RFM95_RST, HIGH); delay(10);

  // Initialize radio and ensure that it is successful
  while (!rf95.init()) ; // Serial.println("LoRa radio init failed");
  //Serial.println("LoRa radio init OK!");

  // Set frequency and ensure that it is successful
  if (!rf95.setFrequency(RF95_FREQ)) ; //Serial.println("setFrequency failed");
  //else Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  // Set the transmit power of the radio
  rf95.setTxPower(23, false);

  // Used for testing. Ensures that reset from watchdog timer is captured on the transmitter
  // Remove for production & actual use to ensure quick reset in the case of a run-time error that forces reset
  delay(5000);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog Reset Timer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Watchdog.enable(WATCHDOG_TIMEOUT); // Enable the watchdog timer

}

// =====================================================================================================
void loop()
{
  stateHandler();
  radio_Update();

  if (missCnt >= RF_DROP_PACKET_DISCONNECT)  // If three packets are missed in a row, we are now in the emergency state
    EmergencyState_RF = true;

  Watchdog.reset(); // Reset the watchdog timer
  // If the line of code above isn't encountered every 10 seconds, the arduino will reset

}

// ====================================================================================================
void stateHandler() {
  EmergencyState_SW = digitalRead(PIN_EMERGENCY_SWITCH);
  if (EMERGENCY_STATE) {    // Will be executed if we are in emergency state
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
void radio_Update() { // This function will respond to the transmitter and send additional information

  len = sizeof(buf);
  if (rf95.waitAvailableTimeout(RF_TIMEOUT_MS)) { //Wait for 1 second for the receiver to respond
    if (rf95.recv(buf, &len)) { // Should be a reply message for us now
      if ((strlen(buf)) == strlen(okMsg)) {
        missCnt = 0; // Reset missCnt as we just had a successful handoff
        //Serial.print("strlen(buf): "); Serial.println(strlen(buf));
        //Serial.print("okMsg: "); Serial.println(strlen(okMsg));
        // Compare the recieved and the known "OK" string
        for (ii = 0; (okMsg[ii] == (char)buf[ii] && ((char)buf[ii] != '\0')); ii++);

        // The emergency state is set if the received string does not match the OK string
        if ( ( ( (char)buf[ii] == '\0' ) && ( okMsg[ii] == '\0' ) ) ) // This is TRUE during normal operation
          EmergencyState_RF = false; // Set EmergencyState_RF to FALSE if the recived message indicates normal operation
        else // Set EmergencyState_RF to TRUE if the recived message indicates emergency operation
          EmergencyState_RF = true;

        stateHandler();
        // Gather and convert battery, RSSI, and switch value into strings
        itoa(measureBattery(), batReading, 10);
        itoa(rf95.lastRssi(), rssiReading, 10);
        if (EmergencyState_SW) itoa(1, switchReading, 10);
        else itoa(0, switchReading, 10);

        // Add the battery, RSSI, and switch value to the buffer for the response
        strcat(buf, " ");
        strcat(buf, batReading);
        strcat(buf, " ");
        strcat(buf, rssiReading);
        strcat(buf, " ");
        strcat(buf, switchReading);

        //Serial.print("Sending: "); Serial.println((char*)buf);


        rf95.send((uint8_t *)buf, sizeof(buf));    // Send a response to the transmitter
        rf95.waitPacketSent();  // Wait until the packet has been sent before continuing
      }
      else {
        missCnt++;
        //Serial.println("Invalid length");
      }
    }
    else { // if receive fails
      missCnt++;
      //Serial.println("Receive failed");
    }
  }
  else { // Encountered if we wait and still fail to receive a response from reciever
    missCnt++;
    //Serial.println("No reply, is there a listener around?");
  }
}

// =========================================Baterry Measurement=========================================
unsigned char measureBattery() {
  measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  percent = 100 * ((measuredvbat - EMPT_V) / (CHRG_V - EMPT_V));
  if (percent > 100) percent = 100;
  return percent;
}

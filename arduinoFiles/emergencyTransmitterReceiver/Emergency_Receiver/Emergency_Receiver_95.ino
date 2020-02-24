#include <SPI.h>
#include <RH_RF95.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* for Feather32u4 RFM9x */
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Blinky on receipt
#define LED 13

#define SIZE_radiopacket 30

volatile unsigned long missCnt = 0;

char okMsg[] = "TempleBoatNormal   ";

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PIN_EMERGENCY_SWITCH 1 /* The pin that the emergency switch is connected to */
volatile byte EmergencyState_RF = true;
volatile byte EmergencyState_SW = true;
volatile byte EmergencyState = true;

volatile byte StateChange = true; /* Set to true so the display is updated the first go around*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Relay Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PIN_MOTOR_RELAY     18
#define PIN_RED_LIGHT       19
#define PIN_BLUE_LIGHT     20
#define PIN_AMBER_LIGHT      21

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Switch Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PIN_EMERGENCY_SWITCH 1

// ======================================Battery Monitor Setup=====================================================
#define VBATPIN              A9
#define CHRG_V               4.2
#define EMPT_V               3.0

void setup()
{
  pinMode(PIN_MOTOR_RELAY, OUTPUT);
  pinMode(PIN_RED_LIGHT, OUTPUT);
  pinMode(PIN_BLUE_LIGHT, OUTPUT);
  pinMode(PIN_AMBER_LIGHT, OUTPUT);

  pinMode(PIN_EMERGENCY_SWITCH, INPUT);
  EmergencyState_SW = digitalRead(PIN_EMERGENCY_SWITCH);
  attachInterrupt(digitalPinToInterrupt(PIN_EMERGENCY_SWITCH), ISR_EmergencyStateChange, CHANGE);

  digitalWrite(PIN_MOTOR_RELAY, HIGH);
  digitalWrite(PIN_RED_LIGHT, HIGH);
  digitalWrite(PIN_BLUE_LIGHT, HIGH);
  digitalWrite(PIN_AMBER_LIGHT, HIGH);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Serial Monitor Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Serial.begin(9600);
  delay(2000);
  Serial.println("Feather LoRa RX Test!");

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  pinMode(LED, OUTPUT);

  pinMode(RFM95_RST, OUTPUT);
  /* Manual reset of the radio */
  digitalWrite(RFM95_RST, HIGH); delay(100);
  digitalWrite(RFM95_RST, LOW);  delay(10);
  digitalWrite(RFM95_RST, HIGH); delay(10);

  while (!rf95.init()) Serial.println("LoRa radio init failed");
  Serial.println("LoRa radio init OK!");
  delay(1000);

  if (!rf95.setFrequency(RF95_FREQ)) Serial.println("setFrequency failed");
  else Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  delay(1000);

  rf95.setTxPower(23, false);
}

// =====================================================================================================
void loop()
{
  if (rf95.waitAvailableTimeout(1000)) {
    if (rf95.available()) {
      radioAvailableExecute();
    }
    else { /* if radio not available */
      missCnt++;
      Serial.println("Radio not available");
    }
  }
  else { /* if radio times-out */
    missCnt++;
    Serial.print("Radio timeout");
  }

  if (missCnt > 2) { /* If three packets are missed in a row, we are now in the emergency state */
    EmergencyState_RF = true;
  }
  
  EmergencyState = EmergencyState_SW || EmergencyState_RF;
  stateHandler();
}

// ====================================================================================================
void stateHandler() {
  if (EmergencyState == true) {
      digitalWrite(LED, HIGH);
      digitalWrite(PIN_MOTOR_RELAY, HIGH);
      digitalWrite(PIN_RED_LIGHT, LOW);
  }
  else {
      digitalWrite(LED, LOW);
      digitalWrite(PIN_MOTOR_RELAY, LOW);
      digitalWrite(PIN_RED_LIGHT, HIGH);
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
 
    if (NormalMessage) {
      EmergencyState_RF = false;
      blinkLED(); /* Blink LED when not in emergency mode to show connection status */
    }
    else{
      EmergencyState_RF = true;
    }

    Serial.print("Got: "); Serial.println((char*)buf);
    Serial.print("RSSI: "); Serial.println(rf95.lastRssi(), DEC);
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
    //rf95.send(buf, sizeof(buf));
    //rf95.waitPacketSent();
    Serial.println("Sent a reply");
  }
  else { /* if receive fails */
    missCnt++;
    Serial.println("Receive failed");
  }
}

void blinkLED(void) {
  digitalWrite(LED, LOW);
  for (int ii = 0; ii < 10; ii++) delayMicroseconds(10000);
  digitalWrite(LED, HIGH);
  for (int ii = 0; ii < 10; ii++) delayMicroseconds(10000);
  digitalWrite(LED, LOW);
}

// =======================================Baterry Measurement=========================================
float measureBattery() {
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  return measuredvbat;
}

//==================On-Boat Button=============================================
void ISR_EmergencyStateChange(void){
  if(EmergencyState_SW != digitalRead(PIN_EMERGENCY_SWITCH)){
    delayMicroseconds(50000);
    if(EmergencyState_SW != digitalRead(PIN_EMERGENCY_SWITCH)){
      EmergencyState_SW = !EmergencyState_SW;
    }
  }
}

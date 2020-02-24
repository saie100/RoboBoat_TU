
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <RH_RF95.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OLED Display Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1   // Reset pin # (sharing Arduino reset pin as it is -1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PIN_EMERGENCY_SWITCH 1 /* The pin that the emergency switch is connected to */
volatile byte EmergencyState;
volatile byte StateChange = true; /* Set to true so the display is updated the first go around*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

#define RF95_FREQ 915.0
RH_RF95 rf95(RFM95_CS, RFM95_INT); /* Singleton instance of the radio driver */
#define LED 13 /* Blinky on receipt */

#define SIZE_radiopacket 30

int16_t packetnum = 0;  // packet counter, we increment per xmission

uint8_t buf[SIZE_radiopacket];
uint8_t len = sizeof(buf);

int16_t rssi = 0;

int16_t successMsgs = 0, failMsgs = 0;

volatile unsigned long missCnt = 0; /* Counts the number of conseuctive misses */
volatile unsigned long discCnt = 0;

int     RxLowBat = 0;
char    RxLowBat_MSG[] = "Rx<10%";

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Battery Monitor Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define VBATPIN A9
#define CHRG_V 4.2
#define EMPT_V 3.0


// =====================================================================================================
void setup() {
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Serial Monitor Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Serial.begin(9600);
  //while (!Serial.available());
  delay(2000);
  Serial.println("The serial monitor has been established");

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Display Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /* Print the success or failure of the serial monitor initialzition in the serial monitor */
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) Serial.println(F("SSD1306 allocation failed"));
  else Serial.println(F("SSD1306 allocation succeeded"));
  display.display(); /* Update the output on the display */
  delay(2000); /* Wait for 2 seconds to ensure that the display has been initialized */

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  /* Manual reset of the radio */
  digitalWrite(RFM95_RST, HIGH); delay(100);
  digitalWrite(RFM95_RST, LOW);  delay(10);
  digitalWrite(RFM95_RST, HIGH); delay(10);

  display.clearDisplay(); /* Clear the display */
  display.setTextSize(1);
  display.setTextColor(WHITE);
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    display.println("LoRa init failed");
    display.display();
  }
  Serial.println("LoRa radio init OK!");
  display.println("LoRa init OK!");
  display.display();
  delay(1000);

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    display.println("setFrequency failed");
    display.display();
  } else {
    Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    display.print("Set Freq to: "); display.println(RF95_FREQ);
    display.display();
    delay(1000);
  }


  rf95.setTxPower(23, false);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /* Configure the pin that the switch is connected to to input - hardware pullup installed on board*/
  pinMode(PIN_EMERGENCY_SWITCH, INPUT);
  /* Set the emergencyState variable to the state of the emergency switch;s input pin */
  EmergencyState = digitalRead(PIN_EMERGENCY_SWITCH);
  /* Enable the ISR for the emergency stop button switch */
  attachInterrupt(digitalPinToInterrupt(PIN_EMERGENCY_SWITCH), ISR_EmergencyStateChange, CHANGE);
}

// =====================================================================================================
void loop() {

  radio_Update();

  /* Disconnect event occurs after three missed transmissions */
  if(missCnt == 3){ 
    discCnt++;
  }
  
  updateDisplay(); /* Update the output on the display */
  for (int ii = 0; ii < 5; ii++) {
    delayMicroseconds(10000);
  }
}

// =====================================================================================================
void ISR_EmergencyStateChange() {
  // Debouncing:
  /* If the new value does not match the old value, there might have been a state change */
  if (EmergencyState != digitalRead(PIN_EMERGENCY_SWITCH)) {
    /* delayMicroseconds() Does not use an ISR timer so it works inside of another ISR */
    delayMicroseconds(50000);
    /* If the new value still does not match the old value, there was a state change */
    if (EmergencyState != digitalRead(PIN_EMERGENCY_SWITCH)) {
      //radio_Update();
      EmergencyState = !EmergencyState; /* Update the EmergencyState variable */
      StateChange = true; /* Set the emergency state to be updated in the loop */
    }
  }
}

// =====================================================================================================
void radio_Update() {
  if (digitalRead(PIN_EMERGENCY_SWITCH) == HIGH) radio_TransmitPacket("TempleBoatEmergency");
  else radio_TransmitPacket("TempleBoatNormal   ");

  if (rf95.waitAvailableTimeout(2000)) {
    if (rf95.recv(buf, &len)) { /* Should be a reply message for us now */
      rssi = rf95.lastRssi();
      successMsgs++;
      missCnt = 0;
      /*Check if Receiver is low power (<10%)*/
      int ii;
      for (ii = 0; (RxLowBat_MSG[ii] == (char)buf[ii] && ((char)buf[ii] != '%')); ii++);
      RxLowBat = (((char)buf[ii] == '%') && (RxLowBat_MSG[ii] == '%'));
      
      Serial.print("Got reply: "); Serial.println((char*)buf);
      Serial.print("RSSI: "); Serial.println(rssi, DEC);
    }
    else {
      rssi = 1; /* Invalid RSSI value to indicate no connection */
      failMsgs++;
      missCnt++; /* Counts the number of conseuctive misses */
      Serial.println("Receive failed");
    }
  }
  else {
    rssi = 2; /* Invalid RSSI value to indicate no connection */
    failMsgs++;
    missCnt++; /* Counts the number of conseuctive misses */
    Serial.println("No reply, is there a listener around?");
  }
}

// =====================================================================================================
void radio_TransmitPacket(char radiopacket[]) {

  //itoa(packetnum++, radiopacket + 13, 10);
  Serial.print("Sending "); Serial.println(radiopacket);
  //radiopacket[SIZE_radiopacket - 1] = 0;

  Serial.println("Sending...");
  rf95.send((uint8_t *)radiopacket, SIZE_radiopacket); /* Sending... */

  Serial.println("Waiting for packet to complete...");
  rf95.waitPacketSent(); /* Waiting for packet to complete... */
}

// =====================================================================================================
void updateDisplay() {
  display.clearDisplay(); /* Clear the display */
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update the Battery Information on the Display ~~~~~~~~~~~~~~~~~~~~~~~~~
  float batPercent = (measureBattery()-EMPT_V) / (CHRG_V-EMPT_V);
  if (batPercent > 1) batPercent = 1;
  display.setCursor(100, 0); display.print((int)(batPercent * 100)); display.println("%");

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update the Radio information on the Display ~~~~~~~~~~~~~~~~~~~~~~~~
  if (rssi < 1) {
    display.setCursor(0, 0);
    display.print("RSSI: "); display.println(rssi);
  }
  if(missCnt <= 2){
    display.setCursor(0, 8);
    display.setTextSize(2);
    if(RxLowBat == 1){
      display.print(RxLowBat_MSG);
    }
    else  display.print("Connected");
  }
  else if (rssi == 1 && missCnt > 2){ /* Ensure that we've missed at least three packets before displaying */
    display.setCursor(0, 8);
    display.setTextSize(2);
    display.print("TIMEOUT");
  }
    else if (rssi == 2 && missCnt > 2){ /* Ensure that we've missed at least three packets before displaying */
    display.setCursor(0, 10);
    display.setTextSize(2);
    display.print("NO ACK");
  }
  display.setCursor(0, 25);
  display.setTextSize(1);
  display.print("Disconnects: "); display.println(discCnt);
  display.print("Miss/Tot: "); 
  display.print(failMsgs); display.print("/"); 
  display.print(failMsgs+successMsgs);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update the Emergency Information on the Display ~~~~~~~~~~~~~~~~~~~~~~~~~
  display.setCursor(0, 45);
  display.setTextSize(2);
  if (digitalRead(PIN_EMERGENCY_SWITCH) == HIGH) {
    display.println("Emergency");
    Serial.println("Emergency Mode Triggered");
  } 
  else {
    display.println("Normal");
    Serial.println("Normal Operation");
  }
  display.display(); /* Update the display */
}


// =====================================================================================================
float measureBattery() {
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  return measuredvbat;
}

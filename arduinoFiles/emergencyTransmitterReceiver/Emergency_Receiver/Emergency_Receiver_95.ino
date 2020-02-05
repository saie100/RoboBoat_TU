// Feather9x_RX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (receiver)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_TX

#include <SPI.h>
#include <RH_RF95.h>

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

// Relay pins
#define CH1 18  //relay to cutoff circuit
#define CH2 19  //red LED
#define CH3 20  //blue LED
#define CH4 21  //Amber LED

// ================== Battery Management ================== 
// Battery voltage measurement pin
#define VBATPIN A9

// Function for calculating battery percentage
void measureBattery(float *measured);

// flot variable that will store hold the battery voltage;
float measuredvbat = 0;

int16_t packetnum = 0;

void setup() 
{
  Serial.begin(115200);
  while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer

  /*Set pinMode and pull up relays' pins(the circuit should be cut off by turning off the relays)*/
  pinMode(LED, OUTPUT);     
  pinMode(RFM95_RST, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  pinMode(CH3, OUTPUT);
  pinMode(CH4, OUTPUT);
  digitalWrite(CH1, HIGH);   //big relay
  digitalWrite(CH2, HIGH);   //red LED turns off initially
  digitalWrite(CH3, LOW);  //blue LED (auto mode) turns on
  digitalWrite(CH4, HIGH);  //amber LED turns off
  digitalWrite(RFM95_RST, HIGH);

  Serial.println("Feather RFM95 RX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  
  while (!rf95.init()) {
    Serial.println("RFM95 radio init failed");
    while (1);
  }
  Serial.println("RFM95 radio init OK!");
  
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while(1);
  }
  Serial.print("Set Freq to: ");  Serial.println(RF95_FREQ);
  // If you are using a high power rf95 eg RFM95HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf95.setTxPower(23, false);  // range from 14-20 for power, 2nd arg must be true for 69HCW
}


void loop() {
 
 if (rf95.available()) {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    
    /* print battery status*/
    measuredvbat = analogRead(VBATPIN);
    measureBattery(&measuredvbat);
    Serial.print("VBat: " );  Serial.println(measuredvbat);

    // receiving a message from transmitter
    if (rf95.recv(buf, &len)) {
      if (!len) return;
      buf[len] = 0;
      Serial.print("Received ["); Serial.print(len);  Serial.print("]: ");  Serial.println((char*)buf);
      Serial.print("RSSI: "); Serial.println(rf95.lastRssi(), DEC);
      digitalWrite(LED, HIGH);
      //only sets relays to high if received "OK"
      if (strstr((char *)buf, "OK")) {
        digitalWrite(CH1, HIGH);
        digitalWrite(CH2, HIGH);
        digitalWrite(CH3, LOW);
        digitalWrite(CH4, HIGH);
        
        // Send a reply! (send back the received words)
        rf95.send(buf, sizeof(buf));
        rf95.waitPacketSent();
        /*rf95.send(measuredvbat, sizeof(float));     //send receiver battery to transmitter
        rf95.waitPacketSent();*/
        Serial.println("Sent a reply");
      }
      //if don't receive "OK", set relays to low
      else{
        digitalWrite(CH1, LOW);
        digitalWrite(CH2, LOW);
        digitalWrite(CH3, HIGH);
        digitalWrite(CH4, HIGH);
      }
    } 
    // not receiving a message from transmitter >> set relays to low
    else {
      Serial.println("Receive failed");
      digitalWrite(CH1, LOW);
      digitalWrite(CH2, LOW);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, HIGH);
    }
 }
 else{
  //lost connecting with transmitter for 5sec >> emergency mode
  unsigned long startTime = millis();
  while((millis() - startTime)<5000 && !(rf95.available()));
  Serial.println("Receive failed");
  digitalWrite(CH1, LOW);
  digitalWrite(CH2, LOW);
  digitalWrite(CH3, HIGH);
  digitalWrite(CH4, HIGH);
 }
 
}

void measureBattery(float *measured){
  *measured *= 2;    // we divided by 2, so multiply back
  *measured *= 3.3;  // Multiply by 3.3V, our reference voltage
  *measured /= 1024; // convert to voltage
}

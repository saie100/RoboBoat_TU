// Feather9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_RX

#include <SPI.h>
#include <RH_RF95.h>

// ================= OLED ======================
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// =================================================

/* for feather32u4 */
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int16_t packetnum = 0;  // packet counter, we increment per xmission

int button_state = 1;
#define E_BUTTON        1   //interrupt pin for E-stop button

#define LED             13
#define VBATPIN         A9  //Battery pin

#define EMPTY_VOLTAGE   3   //low battery energy
#define FULL_VOLTAGE    4.2 //full battery energy


// ==================== OLED PRINTING FUNCTIONS =====================
#define BAT_ROW        30
#define BAT_COL        0

void oled_displayBattery(void){
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setCursor(BAT_COL, BAT_ROW);
  display.print("Battery: ");
  //The voltage of the battery
  double batteryVoltage = ((double)analogRead(VBATPIN))*2*3.3/1024;
  //The % charge of the battery
  int charge = ( (batteryVoltage - EMPTY_VOLTAGE) / (FULL_VOLTAGE - EMPTY_VOLTAGE) ) * 100;
  display.print(charge);
  display.print("%");
}

void setup() 
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

  pinMode(E_BUTTON,INPUT_PULLUP); //setup e_button interrupt pin
  pinMode(VBATPIN,INPUT);
  pinMode(LED, OUTPUT);     
  pinMode(RFM95_RST, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(E_BUTTON), e_stop, CHANGE);
  digitalWrite(RFM95_RST, HIGH);

  Serial.println("Feather RFM95 TX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  
  if (!rf95.init()) {
    Serial.println("RFM95 radio init failed");
    display.clearDisplay();
  
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 30);     // Start at top-left corner
    display.print("RFM95 radio init failed");
    display.display();
    while (1);
  }
  Serial.println("RFM95 radio init OK!");
  
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 30);     // Start at top-left corner
  display.print("RFM95 radio init OK!");
  display.display();
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  // If you are using a high power rf95 eg RFM95HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf95.setTxPower(23, false);  // range from 14-20 for power, 2nd arg must be true for 69HCW
}

void loop() {
  delay(10);  // Wait 1 second between transmits, could also 'sleep' here!
  
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  
  oled_displayBattery();

  if(button_state == 0){ //Emergency functionality
    char radiopacket[] = "STOP";
    Serial.print("Sending "); Serial.println(radiopacket);
    // Send a message!
    rf95.send((uint8_t *)radiopacket, strlen(radiopacket));
    rf95.waitPacketSent();
    display.setCursor(0, 40); 
    display.print("EMERGENCY!!!");
    display.setCursor(0, 50);
    display.print("RSSI: ");
    display.print(rf95.lastRssi());
  }
  else{
    char radiopacket[] = "OK";  //Everything functioning OKAY
    Serial.print("Sending "); Serial.println(radiopacket);
    // Send a message!
    rf95.send((uint8_t *)radiopacket, strlen(radiopacket));
    rf95.waitPacketSent(); 
  
    display.setCursor(0, 40);     
    display.print("ALL CLEAR!!!");
    display.setCursor(0, 50);
    display.print("RSSI: ");
    display.print(rf95.lastRssi()); 
  }
  
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  buf[0] = 0;
  uint8_t len = RH_RF95_MAX_MESSAGE_LEN;
  unsigned long listenTime = millis();
  while((millis() - listenTime) < 2000 && !(rf95.recv(buf, &len)));
  /*received reply from receiver*/
  if (buf[0] != 0) {
    Serial.print("Got a reply: ");
    Serial.println((char*)buf);
    display.setCursor(0, 0);     // Start at top-left corner
    display.print("Connected");
    display.setCursor(0, 10);
    display.print((char*)buf);
  }else{  /*not receiving reply*/
    listenTime = millis();
    while((millis() - listenTime) < 2000);
    if(!(rf95.recv(buf, &len))){
      Serial.println("Receive failed");
      display.setCursor(0, 0);     // Start at top-left corner
      display.print("Disconnected");
    }else{
      display.setCursor(0, 0);
      display.print("Connected");
    }
  }
  display.display();
}

void e_stop(void){
  button_state = !button_state;
}

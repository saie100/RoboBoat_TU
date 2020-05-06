#include <Adafruit_SleepyDog.h> // reset the transmitter if it stops for 10 seconds
#include <Adafruit_SSD1306.h> // Adds OLED display support 
#include <Wire.h> // Adds I2C Oled Support
#include <RH_RF95.h> // Adds support for the LoRa Radio

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define WATCHDOG_TIMEOUT 10000 // Time of inactivity before restarting the arduino

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OLED Display Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1   // Reset pin # (sharing Arduino reset pin as it is -1)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned char displayInitSuccess = 0;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PIN_EMERGENCY_SWITCH 1 // The pin that the emergency switch is connected to
unsigned char Tx_E_Switch;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RFM95_RST 4 // The reset pin for the radio
#define RFM95_INT 7 // Slave select pin for the radio
#define RFM95_CS 8  // Chip select pin for the radio

#define RF95_FREQ 915.0   // Operating frequency of emergency receiver
RH_RF95 rf95(RFM95_CS, RFM95_INT); // Singleton instance of the radio driver

#define RF_DROP_PACKET_DISCONNECT   3 // Number of dropped paxkets that results in a disconnect event
#define RF_TIMEOUT_MS     1000 // How long we should wait for a response before retransmitting

#define SIZE_radiopacket 50 // Max size of transmission

uint8_t buf[SIZE_radiopacket];  // Input buffer for the radio - declared globally to keep out of the stack
uint8_t len; // Holds the actual size of th received message

char *strtok_prt; // Used to tokinize message from the receiver to extract relevant information
unsigned char RxBattery = 0;  // Holds the receiver's battery percentage
unsigned char Rx_E_Switch = 0; // Holds the receiver's emergency switch state

int16_t RxRssi = 2; // Holds the receiver's TxRssi
int16_t TxRssi = 2; // Holds the transmitters TxRssi

volatile unsigned int successMsgs = 0; // Holds the total number of successfuly transmissions
volatile unsigned int failMsgs = 0; // Holds the total number of failed tramsissions

volatile unsigned int missCnt = 0; // Holds the current count of consequitive failed transmissions
volatile unsigned int discCnt = 0;  // Holds the number of disconnect events since power-up

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Battery Monitor Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define VBATPIN A9  // The analog pin connected to the battery
#define CHRG_V 4.2  // The changed voltage of the batter
#define EMPT_V 3.0  // The discharged voltage of the battery

float measuredvbat;
unsigned char percent;

// =====================================================================================================
void setup() {
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Serial Monitor Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //Serial.begin(9600);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Display Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Print the success or failure of the display initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    //Serial.println(F("SSD1306 allocation failed"));
  }
  else {
    //Serial.println(F("SSD1306 allocation succeeded"));
    displayInitSuccess = 1; // Allow the display to be printed to
    display.clearDisplay(); // Clear the display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("SSD1306 allocated");
    display.display(); // Update the output on the display
    delay(250);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radio Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Manual reset of the radio
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH); delay(100);
  digitalWrite(RFM95_RST, LOW);  delay(10);
  digitalWrite(RFM95_RST, HIGH); delay(10);

  // Initialize radio and ensure that it is successful
  while (!rf95.init()) {
    //Serial.println("LoRa radio init failed");
    if(displayInitSuccess) display.println("LoRa init failed");
    if(displayInitSuccess) display.display();
  }
  //Serial.println("LoRa radio init OK!");
  if(displayInitSuccess) display.println("LoRa init OK!");
  if(displayInitSuccess) display.display();
  delay(250);

  // Set frequency and ensure that it is successful
  if (!rf95.setFrequency(RF95_FREQ)) {
    //Serial.println("setFrequency failed");
    if(displayInitSuccess) display.println("setFrequency failed");
    if(displayInitSuccess) display.display();
  } else {
    //Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    if(displayInitSuccess) display.print("Set Freq to: "); display.println(RF95_FREQ);
    if(displayInitSuccess) display.display();
    delay(250);
  }
  // Set the transmit power of the radio
  rf95.setTxPower(23, false);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Configure the pin that the switch is connected to to input - hardware pullup installed on board
  pinMode(PIN_EMERGENCY_SWITCH, INPUT);
  // Set the Tx_E_Switch variable to the state of the emergency switch's input pin
  Tx_E_Switch = digitalRead(PIN_EMERGENCY_SWITCH);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Watchdog Reset Timer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Watchdog.enable(WATCHDOG_TIMEOUT); // Enable the watchdog timer

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Other ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Clear the display and wait 2 seconds (this makes the arduino easier to re-program the arduino)
  if(displayInitSuccess) display.clearDisplay();
  if(displayInitSuccess) display.display();
  delay(2000);
}

// =====================================================================================================
void loop() {

  Tx_E_Switch = digitalRead(PIN_EMERGENCY_SWITCH); // Update the switch value

  radio_Update(); // Try to talk to the receiver

  // Disconnect event occurs after three missed transmissions
  if (missCnt == RF_DROP_PACKET_DISCONNECT) {
    discCnt++;
  }

  if(displayInitSuccess) updateDisplay(); // Update the output on the display

  Watchdog.reset(); // Reset the watchdog timer
  // If the line of code above isn't encountered every 10 seconds, the arduino will reset
}

// =====================================================================================================
void radio_Update() {
  if (Tx_E_Switch == HIGH)    radio_TransmitPacket("TempleBoatEmerge"); // Transmit emergency message
    else                          radio_TransmitPacket("TempleBoatNormal");  // Transmit normal message
  
  len = sizeof(buf);
  if (rf95.waitAvailableTimeout(RF_TIMEOUT_MS)) { //Wait for 1 second for the receiver to respond
    if (rf95.recv(buf, &len)) { // Should be a reply message for us now
      TxRssi = rf95.lastRssi(); // Update the TxRssi value using the last message
      successMsgs++; // Increment the successful message count
      missCnt = 0;  // Reset missCnt as we just had a successful handoff

      //Serial.print("Got reply: "); Serial.println((char*)buf);
      //Serial.print("TxRssi: "); Serial.println(TxRssi, DEC);

      // Parse the received buffer for tokenized message while ensureing that
      // null isnt encxoutered as this would indicate an invalid message
      strtok_prt = strtok (buf, " ");
      strtok_prt = strtok (NULL, " ");
      RxBattery = atoi(strtok_prt);
      strtok_prt = strtok (NULL, " ");
      RxRssi = atoi(strtok_prt);
      strtok_prt = strtok (NULL, " ");
      Rx_E_Switch = atoi(strtok_prt);

    }
    else { // shouldn't be encountered as rf95.recv will only execute if there is a message available
      TxRssi = 1; // Invalid TxRssi value to indicate no connection
      failMsgs++;
      missCnt++; // Counts the number of conseuctive misses
      //Serial.println("Receive failed");
    }
  }
  else { // Encountered if we wait and still fail to receive a response from reciever
    TxRssi = 2; // Invalid TxRssi value to indicate no connection
    failMsgs++;
    missCnt++; // Counts the number of conseuctive misses
    //Serial.println("No reply, is there a listener around?");
  }
}

// =====================================================================================================
void radio_TransmitPacket(char radiopacket[]) {
  //Serial.print("Sending "); Serial.println(radiopacket);

  //Serial.println("Sending...");
  rf95.send((uint8_t *)radiopacket, SIZE_radiopacket); // Send the packet

  //Serial.println("Waiting for packet to complete...");
  rf95.waitPacketSent(); // Wait for the packet to be sent
}

// =====================================================================================================
void updateDisplay() {
  display.clearDisplay(); // Clear the display
  display.setTextSize(1); // Set the text size to 1
  display.setTextColor(WHITE); // Clear the font color to white

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update the Battery/Rssi Information on the Display ~~~~~~~~~~~~~~~~~~~~
  // display the transmitter's RSSI
  display.setCursor(0, 0); display.print("Tx-RSSI:"); display.print(TxRssi);
  // display the transmitter's batter
  display.setCursor(85, 0); display.print("Tx:"); display.print(measureBattery()); display.print("%"); y

  // Draw the line to separate the Rx and Tx Battery/Rssi Information
  display.drawFastHLine(0, 8, 128, WHITE);

  // display the receivers's RSSI
  display.setCursor(0, 10); display.print("Rx-RSSI:"); display.print(RxRssi); 
  // Display the receiver's battery
  display.setCursor(85, 10); display.print("Rx:"); display.print(RxBattery); display.print("%"); 

  // Draw the line to separate the Battery/Rssi Information from the packet information table
  display.drawFastHLine(0, 18, 128, WHITE); 
  display.drawFastHLine(0, 19, 128, WHITE); 
  display.drawFastHLine(0, 20, 128, WHITE);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update the Packet information on the Display ~~~~~~~~~~~~~~~~~~~~~
  display.drawFastHLine(0, 30, 128, WHITE); // Draw middle row line for the packet table
  // Draw first column for packet table
  display.drawFastVLine(27, 20, 24, WHITE); 
  display.drawFastVLine(28, 20, 24, WHITE); 
  // Draw second column for packet table
  display.drawFastVLine(65, 20, 24, WHITE); 
  display.drawFastVLine(66, 20, 24, WHITE); 

  // Add the column titles for the packet table
  display.setCursor(0, 22); display.print("Disc");
  display.setCursor(31, 22); display.print("Drop");
  display.setCursor(69, 22); display.print("Total");

  // Add the column content for the packet table
  display.setCursor(0, 33); display.print(discCnt);
  display.setCursor(31, 33); display.print(failMsgs);
  display.setCursor(69, 33); display.print(failMsgs + successMsgs);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update the Switch/Emergency Information on the Display ~~~~~~~~~~~~~~~~~~
  // Draw the boundary for the switch/connection state table
  display.drawFastHLine(0, 43, 128, WHITE); display.drawFastHLine(0, 44, 128, WHITE); 
  display.drawFastHLine(0, 45, 128, WHITE); display.drawFastVLine(113, 45, 19, WHITE); 
  display.drawFastVLine(112, 45, 19, WHITE); display.drawFastVLine(111, 45, 19, WHITE);

  display.setTextSize(2);
  display.setCursor(0, 48);
  // Print the switch state on the display
  if (Tx_E_Switch || Rx_E_Switch) display.println("STOP");
  else display.println("NORMAL");
  

  display.setCursor(116, 48);
  // Print the conenction status on the display
  if (successMsgs > 0 && missCnt < RF_DROP_PACKET_DISCONNECT) display.print("C"); // Print if connected
  // Ensure that we've missed at least three packets before displaying
  else if (TxRssi == 1 && missCnt >= RF_DROP_PACKET_DISCONNECT) display.print("T"); 
  // Ensure that we've missed at least three packets before displaying
  else if (TxRssi == 2 && missCnt >= RF_DROP_PACKET_DISCONNECT) display.print("N"); 
  else display.print("E"); // Handles undefined error condition

  display.display(); // Update the display */
}

// =====================================================================================================
unsigned char measureBattery() {
  measuredvbat = analogRead(VBATPIN); // Read analog values
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  percent = 100 * ((measuredvbat - EMPT_V) / (CHRG_V - EMPT_V)); // Convert to percent
  if (percent > 100) percent = 100; // Ensure percent is less that 100%
  return percent;
}

#include <ros.h>
#include <std_msgs/String.h>

float convert = 5.0 / 1023; // Converts ADC to voltage
const float scale[6] = { // values for scaling voltage
  1.0,
  (470.0 + 560.0) / 470.0,
  (330.0 + 560.0) / 330.0,
  (180.0 + 560.0) / 180.0,
  (150.0 + 560.0) / 150.0,
  (100.0 + 560.0) / 100.0
};

// Obtained from the averge of the diffreences between multimeter and arduino at 6 different voltages
// These are applied to the voltage measurement reference to ground (negative terminal) of the battery
const float offset_6s[] = {0.0688, 0.1050, 0.3200, 0.2000, 0.3817, 0.6283};
const float offset_4s[] = {0.0667, 0.0817, 0.2617, 0.2100};
const float offset_3s[] = {0.0688, 0.0550, 0.3467};
const float offset_32s[] = {0.0667, 0.0550, 0.3067};

int bat0Pins[] = {A5, A4, A3, A2, A1, A0};
int bat0CellCnt = 6;
int bat1Pins[] = {A6, A7, A8, A9};
int bat1CellCnt = 4;
int bat2Pins[] = {A12, A11, A10};
int bat2CellCnt = 3;
int bat3Pins[] = {A13, A14, A15};
int bat3CellCnt = 3;

float measured[6]; // Holds the measured voltages

#define runAvgCnt 100 // Number of samples in the running-average
#define SEQ_DELAY 100 // Time in ms between measuring batteries
#define SAMPLE_DELAY 10 // Time in ms between running-average sample collections

// Creating the nh NodeHandle which represents the battery monitor ROS node
ros::NodeHandle nh;
// Creating the ROS string message variable
std_msgs::String BatteryVoltage;
// Defining the publisher and the topic name
ros::Publisher BatteryVoltage_pub("BatteryVoltage", &BatteryVoltage);

void setup() {
  Serial.begin(57600);
  
  // initialize the ROS serial node
  nh.initNode();
  // Make battery monitor topic visible on the network
  nh.advertise(BatteryVoltage_pub);

  // Enable all pullup resistors for the analog pins
  setPULUP(bat0Pins, bat0CellCnt);
  setPULUP(bat1Pins, bat1CellCnt);
  setPULUP(bat2Pins, bat2CellCnt);
  setPULUP(bat3Pins, bat3CellCnt);
}

void loop() {
  String message = ""; // Clear the string containing all battery readings
  
    // Measure the 6s battery
    measure_cell(bat0Pins, bat0CellCnt, offset_6s);
    // Convert battery measurements in to string with the cell measurements separated by spaces
    for(int i = 0; i < bat0CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1); // Remove extra space in the string
    message += ","; // Separate battery measurements with commas
    
    // Measure the 4s battery
    measure_cell(bat1Pins, bat1CellCnt, offset_4s);
    // Convert battery measurements in to string with the cell measurements separated by spaces
    for(int i = 0; i < bat1CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1); // Remove extra space in the string
    message += ","; // Separate battery measurements with commas
    
    // Measure the 3s (1) battery
    measure_cell(bat2Pins, bat2CellCnt, offset_3s);
    // Convert battery measurements in to string with the cell measurements separated by spaces
    for(int i = 0; i < bat2CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1); // Remove extra space in the string
    message += ","; // Separate battery measurements with commas

    // Measure the 3s (2) battery
    measure_cell(bat3Pins, bat3CellCnt, offset_32s);
    // Convert battery measurements in to string with the cell measurements separated by spaces
    for(int i = 0; i < bat3CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1); // Remove extra space in the string   

    // Publish the battery monitor readings
    BatteryVoltage.data = message.c_str(); 
    BatteryVoltage_pub.publish(&BatteryVoltage);
    nh.spinOnce();
}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt,// number of cells in the battery we are measuring
                  const float offset[] // The cell-specific resistor error correction array
                  ) {

  disablePULUP(pins, pinCnt); // Disable pullup resistors on the pins that we are reading

  float avg[] = {0, 0, 0, 0, 0, 0}; // Holds the running-average
  for (int j = 0; j < runAvgCnt; j++) { // Loop over the number of average samples
    for (int i = 0; i < pinCnt; i++) {  // Loop over the number of pins in the battery we are measuring
      avg[i] += analogRead(pins[i]); // Add ADC readings to  an array to calculate running-average
    }
    delay(SAMPLE_DELAY); //  Wait between each collection of analog readings
  }
  
  // Compute average and scale back between 0 and 5V
  for (int i = 0; i < pinCnt; i++) measured[i] = (avg[i] / runAvgCnt) * convert; 

  // compensate for voltage divider and resistance errors
  for (int i = 0; i < pinCnt; i++) measured[i] = (measured[i] * scale[i]) + offset[i]; 

  // Calculating individual cell voltages
  for (int i = pinCnt - 1; i > 0; i--) measured[i] = measured[i] - measured[i - 1]; 
  
  // Zero the output if battery not plugged in
  for (int i = 0; i < pinCnt; i++) if(measured[i] < 1) measured[i] = 0; 

  // Set the pullup resistors on the pins that we just read from
  setPULUP(pins, pinCnt);
}

void disablePULUP(const int pins[], int pinCnt) {
  for (int i = 0; i < pinCnt; i++) {
    pinMode(pins[i], INPUT);
  }
}

void setPULUP(const int pins[], int pinCnt) {
  for (int i = 0; i < pinCnt; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
}

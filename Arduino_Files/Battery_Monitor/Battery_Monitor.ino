#include <ros.h>
#include <std_msgs/String.h>

float convert = 5.0 / 1024; // converts raw data to voltage
const float scale[6] = { // values for scaling voltage
  1.0,
  (470.0 + 560.0) / 470.0,
  (330.0 + 560.0) / 330.0,
  (180.0 + 560.0) / 180.0,
  (150.0 + 560.0) / 150.0,
  (100.0 + 560.0) / 100.0
};

// Zeroed Scale - used for collecting data while testing precision/accuracy of the battery monitor
/*
  const float scale6s[] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  const float scale4s[] = {0.00, 0.00, 0.00, 0.00};
  const float scale3s[] = {0.00, 0.00, 0.00};
  const float scale32s[] = {0.00, 0.00, 0.00};
*/

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

#define runAvgCnt 100
#define SEQ_DELAY 100
#define SAMPLE_DELAY 10

ros::NodeHandle nh;

std_msgs::String BatteryVoltage;

ros::Publisher BatteryVoltage_pub("BatteryVoltage", &BatteryVoltage);


void setup() {
  Serial.begin(57600);


  nh.initNode();
  
  nh.advertise(BatteryVoltage_pub);

  setPULUP(bat0Pins, bat0CellCnt);
  setPULUP(bat1Pins, bat1CellCnt);
  setPULUP(bat2Pins, bat2CellCnt);
  setPULUP(bat3Pins, bat3CellCnt);
}


void loop() {
  String message = "";
  
    measure_cell(bat0Pins, bat0CellCnt, offset_6s);
    for(int i = 0; i < bat0CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1);   
    message += ",";
    
    measure_cell(bat1Pins, bat1CellCnt, offset_4s);
    for(int i = 0; i < bat1CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1);   
    message += ",";
    
    measure_cell(bat2Pins, bat2CellCnt, offset_3s);
    for(int i = 0; i < bat2CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1);
    message += ",";

    measure_cell(bat3Pins, bat3CellCnt, offset_32s);
    for(int i = 0; i < bat3CellCnt; i++) message += String(measured[i], 2) + " ";
    message.remove(message.length()-1);   

    //Serial.println(message);
    BatteryVoltage.data = message.c_str();
    BatteryVoltage_pub.publish(&BatteryVoltage);
    nh.spinOnce();
}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt,// number of cells
                  const float offset[]) {


  disablePULUP(pins, pinCnt);

  float avg[] = {0, 0, 0, 0, 0, 0};
  for (int j = 0; j < runAvgCnt; j++) {
    for (int i = 0; i < pinCnt; i++) {
      avg[i] += analogRead(pins[i]); // Add the readings on the pins into an array to calculate running-average
    }
    delay(SAMPLE_DELAY); //  Wait 10ms between each collection of analog readings
  }
  
  for (int i = 0; i < pinCnt; i++) measured[i] = (avg[i] / runAvgCnt) * convert; // Compute average and scale back between 0 and 5V
  
  for (int i = 0; i < pinCnt; i++) measured[i] = (measured[i] * scale[i]) + offset[i]; // compensate for voltage divider and resistance errors

  for (int i = pinCnt - 1; i > 0; i--) measured[i] = measured[i] - measured[i - 1]; // Calculating individual cell voltages

  for (int i = 0; i < pinCnt; i++) if(measured[i] < 1) measured[i] = 0; // Zero the output if battery not plugged in

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

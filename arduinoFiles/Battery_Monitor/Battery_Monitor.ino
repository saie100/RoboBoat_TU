//#include <ros.h>
//#include <std_msgs/String.h>
float convert = 5.0 / 1023; // converts raw data to voltage
char volts[16] = {};// char array that stores cell voltages
int voltsCnt = 0;  // used to index char array
int batteryHealth = 1; // 1-healthy, 2-moderate, 3-low
float constant[6] = { // values for scaling voltage
  1.0000,
  2.1915,
  2.6970,
  4.1111,
  4.7333,
  6.6000,
};
int bat0Pins[] = {A0, A1, A2, A3, A4, A5};
int bat0CellCnt = 6;
int bat0Dir = 0;  // direction of battery
int bat1Pins[] = {A6, A7, A8, A9};
int bat1CellCnt = 4;
int bat1Dir = 1;
int bat2Pins[] = {A10, A11, A12};
int bat2CellCnt = 3;
int bat2Dir = 0;
int bat3Pins[] = {A13, A14, A15};
int bat3CellCnt = 3;
int bat3Dir = 1;


void setup() {
  Serial.begin(9600);
  while(!Serial.available());
    delay(3000);

  Serial.print("HERE");

}


void loop() {


Serial.print("HERE");

  double measuredVoltage[bat0CellCnt];
  measure_cell(bat0Pins, bat0CellCnt, bat0Dir, measuredVoltage);

  measuredVoltage[bat1CellCnt];
  measure_cell(bat1Pins, bat1CellCnt, bat1Dir, measuredVoltage);

  measuredVoltage[bat2CellCnt];
  measure_cell(bat2Pins, bat2CellCnt, bat2Dir, measuredVoltage);

  measuredVoltage[bat3CellCnt];
  measure_cell(bat3Pins, bat3CellCnt, bat3Dir, measuredVoltage);

  //Serial.println(volts);
  delay(3000);

}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt,// number of cells
                  int dir,
                  double measured[] ) { // returning measured analog values through an array
  double currentV = 0;
  double prevV = 0;
  if (dir == 1) {
    Serial.print("here");
    for (int i = 0; i < pinCnt; i++) {
      currentV = analogRead(pins[i]) * convert * constant[i]; // stores voltage of a cell
      currentV = currentV - prevV; // isolates cell voltage
      Serial.println(currentV);
      dtostrf(currentV, 3, 2, volts[voltsCnt]); // stores isolated cell value in array, voltsCnt is the index variable
      measured[i] = currentV; // voltage is stored in an array called measured for later use to test battery health
      prevV = currentV; // current is now stored in previous
      voltsCnt++; // index for char array
      if (voltsCnt == 17) { // theres 16 slots, resets when the array is filled
        voltsCnt = 0;
      }
    }

    if (dir == 0) {
      Serial.print("Here");
      for (int i = pinCnt - 1; i >= 0; i--) {
        currentV = analogRead(pins[i]) * convert * constant[pinCnt - i - 1];
        currentV = currentV - prevV;
        Serial.println(currentV);
        dtostrf(currentV, 3, 2, volts[voltsCnt]);
        measured[i] = currentV;
        prevV = currentV;
        voltsCnt++; // index for char array
        if (voltsCnt == 17) { // theres 16 slots
          voltsCnt = 0;
        }
      }
    }

    batteryStatus(pinCnt, measured);
  }

}

void batteryStatus(int j, double voltages[]) {
  for (int i = 0; i < j; i++) {
    double voltage = voltages[i];

    if (voltage > 3.95) {
      batteryHealth = 1; // healthy
    }
    else if (voltage > 3.55) {
      batteryHealth = 2; // moderate
    }
    else {
      batteryHealth = 3; // Low
    }
  }

  Serial.println();
  //delay(1000);
}

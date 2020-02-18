//#include <ros.h>
//#include <std_msgs/String.h>
float convert = 5.0 / 1023; // converts raw data to voltage
char volts[16] = {};// char array that stores cell voltages
int voltsCnt = 0;  // used to index char array
int batteryHealth = 1; // 1-healthy, 2-moderate, 3-low
float constant[6] = { // values for scaling voltage
  1.0,
  (470.0 + 560.0) / 470.0,
  (330.0 + 560.0) / 330.0,
  (180.0 + 560.0) / 180.0,
  (150.0 + 560.0) / 150.0,
  (100.0 + 560.0) / 100.0
};

const float scale6s[] = {
.0522,
.0075,
.2258,
-0.1907,
0.1719,
0.2047
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

const int runAvgCnt = 14;
float runAvg[6][15];
float runAvgRes[6];
int runAvgIdx = 0;


void setup() {
  Serial.begin(9600);
  // while(!Serial.available());
  //delay(3000);


}


void loop() {



  double measuredVoltage[bat0CellCnt];
  Serial.println("6 cell battery");
  measure_cell(bat0Pins, bat0CellCnt, bat0Dir, measuredVoltage);
  /*
    measuredVoltage[bat1CellCnt];
    measure_cell(bat1Pins, bat1CellCnt, bat1Dir, measuredVoltage);
    measuredVoltage[bat2CellCnt];
    measure_cell(bat2Pins, bat2CellCnt, bat2Dir, measuredVoltage);
    measuredVoltage[bat3CellCnt];
    measure_cell(bat3Pins, bat3CellCnt, bat3Dir, measuredVoltage);
  */
  //Serial.println(volts);
  delay(3000);
  Serial.println();
}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt,// number of cells
                  int dir,
                  double measured[] ) { // returning measured analog values through an array
  double currentV = 0;
  double prevV = 0;
  double sumV = 0;
  if (dir == 1) {
    for (int i = 0; i < pinCnt; i++) {
      Serial.println("error");
      currentV = analogRead(pins[i]) * convert * constant[i]; // stores voltage of a cell
      currentV = currentV - prevV; // isolates cell voltage
      Serial.println(currentV,4);
      //dtostrf(currentV, 3, 2, volts[voltsCnt]); // stores isolated cell value in array, voltsCnt is the index variable
      //measured[i] = currentV; // voltage is stored in an array called measured for later use to test battery health
      prevV = currentV; // current is now stored in previous
      voltsCnt++; // index for char array


      runAvg[runAvgIdx % runAvgCnt][i] = currentV;
    }
    runAvgIdx++;

    for (int j = 0; j < runAvgCnt; j++) {
      runAvgRes[j] = 0;
      for (int i = 0; i < pinCnt; i++) {
        runAvgRes[j] += runAvg[j][i];
      }
      runAvgRes[j] /= runAvgCnt;
      Serial.print("Run Average Cell "); Serial.print(j + 1); Serial.print(": "); Serial.println(runAvgRes[j],4);
    }
  }

  if (dir == 0) {
    for (int i = pinCnt - 1; i >= 0; i--) {
      currentV = analogRead(pins[i]) * convert * constant[pinCnt - i - 1];
      currentV = currentV - prevV;
      Serial.print("Cell "); Serial.print(i + 1); Serial.print(": ");
      //Serial.println(currentV,4);
      Serial.println(currentV+ scale6s[pinCnt - i - 1],4);
      //dtostrf(currentV, 3, 2, volts[voltsCnt]);
      //measured[i] = currentV;
      prevV += currentV;
      //runAvg[runAvgIdx % runAvgCnt][i] = currentV;
      runAvg[i][runAvgIdx] = currentV;
    }
    runAvgIdx++;
   
    for (int j = pinCnt-1; j >=0; j--) {
      runAvgRes[j] = 0;
      for (int i = 0; i < runAvgCnt; i++) {
        runAvgRes[j] += runAvg[j][i];
      }
      runAvgRes[j] /= runAvgCnt;


      Serial.print("Run Average Cell "); Serial.print(j + 1); Serial.print(": "); Serial.println(runAvgRes[j]+scale6s[pinCnt-j-1],4);
    }
  }
  if (runAvgIdx > runAvgCnt) {
    runAvgIdx = 0;
  }
}



void batteryStatus(int j, double voltages[]) {
  for (int m = 0; m < j; m++) {
    double voltage = voltages[m];

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

float convert = 5.0 / 1023; // converts raw data to voltage
const float constant[6] = { // values for scaling voltage
  1.0,
  (470.0 + 560.0) / 470.0,
  (330.0 + 560.0) / 330.0,
  (180.0 + 560.0) / 180.0,
  (150.0 + 560.0) / 150.0,
  (100.0 + 560.0) / 100.0
};


const float scale6s[] = {-0.04, -0.11, 0.19, -0.29, 0.11, 0.11};
const float scale4s[] = {-0.05, -0.13, 0.12, -0.21};
const float scale3s[] = {-0.04, -0.15, 0.21};
const float scale32s[] = {-0.04, -0.16, 0.24};
int bat0Pins[] = {A5, A4, A3, A2, A1, A0};
int bat0CellCnt = 6;
int bat1Pins[] = {A6, A7, A8, A9};
int bat1CellCnt = 4;
int bat2Pins[] = {A12, A11, A10};
int bat2CellCnt = 3;
int bat3Pins[] = {A13, A14, A15};
int bat3CellCnt = 3;
const int runAvgCnt = 100 - 1;
float runAvg[6][runAvgCnt + 1];
float runAvgRes[6];
int runAvgIdx = 0;
void setup() {
  Serial.begin(9600);
}


void loop() {
  double measuredVoltage[bat0CellCnt];
  Serial.println("6 cell battery");
  measure_cell(bat0Pins, bat0CellCnt, scale6s, measuredVoltage);

  measuredVoltage[bat1CellCnt];
  Serial.println("4 cell battery");
  measure_cell(bat1Pins, bat1CellCnt, scale4s, measuredVoltage);

  measuredVoltage[bat2CellCnt];
  Serial.println("3 cell battery");
  measure_cell(bat2Pins, bat2CellCnt, scale3s, measuredVoltage);

  measuredVoltage[bat3CellCnt];
  Serial.println("3(2) cell battery");
  measure_cell(bat3Pins, bat3CellCnt, scale32s, measuredVoltage);

  //Serial.println(volts);
  delay(30000);
  Serial.println();
}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt,// number of cells
                  const float scale[],
                  double measured[] ) { // returning measured analog values through an array

  runAvgIdx = 0;
  for (int num = 0; num < runAvgCnt; num++) {
    float currentV = 0;
    float prevV = 0;
    for (int i = 0; i < pinCnt; i++) {
      currentV = analogRead(pins[i]) * convert * constant[i]; // stores voltage of a cell
      currentV = currentV - prevV; // isolates cell voltage
      //Serial.println(currentV + scale[i], 4);
      prevV += currentV; // current is now stored in previous
      runAvg[i][runAvgIdx] = currentV;
      delay(1);
    }
    runAvgIdx++;
  }
  for (int j = 0; j < pinCnt; j++) {
    runAvgRes[j] = 0;
    for (int i = 0; i < runAvgCnt; i++) {
      runAvgRes[j] += runAvg[j][i];
    }
    runAvgRes[j] /= runAvgCnt;
    Serial.print("Run Average Cell "); Serial.print(j + 1); Serial.print(": ");
    Serial.println(runAvgRes[j] + scale[j], 2);
  }
  Serial.println();
}

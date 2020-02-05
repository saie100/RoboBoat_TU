
float convert = 5.0 / 1023; // converts raw data to voltage
char volts[16] = {};
int voltsCnt = 0;
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
int bat1Pins[] = {A6, A7, A8, A9};
int bat1CellCnt = 4;
int bat2Pins[] = {A10, A11, A12};
int bat2CellCnt = 3;
int bat3Pins[] = {A13, A14, A15};
int bat3CellCnt = 3;


void setup() {
  Serial.begin(9600);
  int bat0Capacity = 0;
  int bat1Capacity = 0;
  int bat2Capacity = 0;
  int bat3Capacity = 0;

}


void loop() {
  



  double measuredVoltage[bat0CellCnt];
  measure_cell(bat0Pins, bat0CellCnt, measuredVoltage);

  measuredVoltage[bat1CellCnt];
  measure_cell(bat1Pins, bat1CellCnt, measuredVoltage);

  measuredVoltage[bat2CellCnt];
  measure_cell(bat2Pins, bat2CellCnt, measuredVoltage);

  measuredVoltage[bat3CellCnt];
  measure_cell(bat3Pins, bat3CellCnt, measuredVoltage);

  Serial.print(volts);
  delay(3000);

}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt, // number of cells
                  double measured[] ) { // returning measured analog values through an array
  double currentV = 0;
  double prevV = 0;
  for (int i = 0; i < pinCnt; i++) {
    currentV = analogRead(pins[i]) * convert * constant[i];
    currentV = currentV - prevV;
    dtostrf(currentV, 3, 2, volts[voltsCnt]);
    measured[i] = currentV;
    prevV = currentV;
    voltsCnt++; // index for char array
    if (voltsCnt == 17) { // theres 16 slots
      voltsCnt = 0;
    }
     batteryStatus(pinCnt, measured);
  }

}

void batteryStatus(int j, double voltages[]) {
  for (int i = 0; i < j; i++) {
    double voltage = voltages[i];

    Serial.print("cell voltage ");
    Serial.print(" is ");
    Serial.print(voltage);
    Serial.println();

    if (voltage > 3.95) {
      batteryHealth =1;  // healthy
    }
    else if (voltage > 3.55) {
      batteryHealth=2; // moderate
    }
    else {
      batteryHealth=3; // Low
    }
  }

  Serial.println();
}

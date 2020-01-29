
float convert = 5.0 / 1023; // converts raw data to voltage
char volts[11] = {};
float constant[6] = { // values for scaling voltage
  1,
  2.196759259,
  2.697299858,
  4.099352052,
  4.737104825,
  6.690951821
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

  //dtostrf();

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



}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt, // number of cells
                  double measured[] ) { // returning measured analog values through an array
  double currentV = 0;
  double prevV = 0;
  for (int i = 0; i < pinCnt; i++) {
    measured[i] = analogRead(pins[i]) * convert * constant[i];
    currentV = measured[i];
    currentV = currentV - prevV;
    prevV = currentV;

  }
  //message(measured, pinCnt);
  batteryStatus(pinCnt, measured);
  Serial.println();
  Serial.println();
  delay(10000);
}







void message(double nums[], int len) {
  double digits;
  int digit;
  int k = 0;
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == 0) {
        digits = nums[i];
        digit = digits;
        volts[k] = digit;
      }
      else if (j == 1) {
        digits = nums[i] * 10;
        digit = digits;
        digit = digit % 10;
        volts[k] = digit;
      }
      else if (j == 2) {
        digits = nums[i] * 100;
        digit = digits;
        digit = digit % 10;
        volts[k] = digit + 48;
      }
      Serial.print(volts);
      k++;

    }
    Serial.println();
  }

}



void batteryStatus(int j, double voltages[]) {
  for (int i = 0; i < j; i++) {
    double voltage = voltages[i];

    Serial.print("cell voltage ");
    Serial.print(" is ");
    Serial.print(voltage);
    Serial.println();




    switch (i) {
      case 0:
        if (voltage > 3.95) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is healthy");
        }
        else if (voltage > 3.55) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is moderate");
        }
        else {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" needs to charge");
        }
        break;
      case 1:
        if (voltage > 7.9) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is healthy");
        }
        else if (voltage > 7.1) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is moderate");
        }
        else {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" needs to charge");
        }
        break;

      case 2:
        if (voltage > 11.85) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is healthy");
        }
        else if (voltage > 10.65) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is moderate");
        }
        else {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" needs to charge");
        }
        break;

      case 3:
        if (voltage > 15.8) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is healthy");
        }
        else if (voltage > 14.2) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is moderate");
        }
        else {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" needs to charge");
        }
        break;

      case 4:
        if (voltage > 19.75) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is healthy");
        }
        else if (voltage > 17.75) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is moderate");
        }
        else {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" needs to charge");
        }
        break;

      case 5: if (voltage > 23.7) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is healthy");
        }
        else if (voltage > 21.3) {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" is moderate");
        }
        else {
          Serial.print("cell ");
          Serial.print(i + 1);
          Serial.print(" needs to charge");
        }
        break;

      default:
        Serial.println("failed");
    }
    Serial.println();
  }


}

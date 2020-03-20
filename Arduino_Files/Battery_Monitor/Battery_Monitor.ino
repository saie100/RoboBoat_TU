#define PRINT_6S true
#define PRINT_4S true
#define PRINT_3SA true
#define PRINT_3SB true

#define SEQ_DELAY 1000

float convert = 5.0 / 1024; // converts raw data to voltage
const float constant[6] = { // values for scaling voltage
  1.0,
  (470.0 + 560.0) / 470.0,
  (330.0 + 560.0) / 330.0,
  (180.0 + 560.0) / 180.0,
  (150.0 + 560.0) / 150.0,
  (100.0 + 560.0) / 100.0
};

// Original scale values obtained. These are applied to indivial cell voltages referenced 
// to their immediate lower-voltage cell
/*
  const float scale6s[] = {0.09, 0.06, 0.25, -0.11, 0.21, 0.25};
  const float scale4s[] = {0.05, 0.01, 0.18, -0.01};
  const float scale3s[] = {0.09, 0.0, 0.35};
  const float scale32s[] = {0.09, -0.01, 0.29};
*/

// Zeroed Scale - used for collecting data while testing precision/accuracy of the battery monitor
/*
const float scale6s[] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
const float scale4s[] = {0.00, 0.00, 0.00, 0.00};
const float scale3s[] = {0.00, 0.00, 0.00};
const float scale32s[] = {0.00, 0.00, 0.00};
*/

// Obtained from the averge of the diffreences between multimeter and arduino at 6 different voltages
// These are applied to the voltage measurement reference to ground (negative terminal) of the battery
const float scale6s[] = {0.0688, 0.1050, 0.3200, 0.2000, 0.3817, 0.6283};
const float scale4s[] = {0.0667, 0.0817, 0.2617, 0.2100};
const float scale3s[] = {0.0688, 0.0550, 0.3467};
const float scale32s[] = {0.0667, 0.0550, 0.3067};

int bat0Pins[] = {A5, A4, A3, A2, A1, A0};
int bat0CellCnt = 6;
int bat1Pins[] = {A6, A7, A8, A9};
int bat1CellCnt = 4;
int bat2Pins[] = {A12, A11, A10};
int bat2CellCnt = 3;
int bat3Pins[] = {A13, A14, A15};
int bat3CellCnt = 3;
const int runAvgCnt = 100;
float runAvg[6][runAvgCnt + 1];
float runAvgRes[6];
int runAvgIdx = 0;


void setup() {
  Serial.begin(9600);
  
  setPULUP(bat0Pins, bat0CellCnt);
  setPULUP(bat1Pins, bat1CellCnt);
  setPULUP(bat2Pins, bat2CellCnt);
  setPULUP(bat3Pins, bat3CellCnt);
}


void loop() {
  double measuredVoltage[6];
  if (PRINT_6S) {
    delay(SEQ_DELAY);
    //double measuredVoltage[6];
    Serial.println("6 cell battery");
    measure_cell(bat0Pins, bat0CellCnt, scale6s, measuredVoltage);
  }

  if (PRINT_4S) {
    delay(SEQ_DELAY);
    //measuredVoltage[bat1CellCnt];
    Serial.println("4 cell battery");
    measure_cell(bat1Pins, bat1CellCnt, scale4s, measuredVoltage);
  }

  if (PRINT_3SA) {
    delay(SEQ_DELAY);
    //measuredVoltage[bat2CellCnt];
    Serial.println("3 cell battery");
    measure_cell(bat2Pins, bat2CellCnt, scale3s, measuredVoltage);
  }

  if (PRINT_3SB) {
    delay(SEQ_DELAY);
    //measuredVoltage[bat3CellCnt];
    Serial.println("3(2) cell battery");
    measure_cell(bat3Pins, bat3CellCnt, scale32s, measuredVoltage);
  }

}

void measure_cell(const int pins[], // analog pin numbers from lowest voltage to highest voltgage
                  int pinCnt,// number of cells
                  const float scale[],
                  double measured[] ) { // returning measured analog values through an array

  disablePULUP(pins, pinCnt);

  float avg[] = {0, 0, 0, 0, 0, 0};
  for (int j = 0; j < runAvgCnt; j++) {
    for (int i = 0; i < pinCnt; i++) {
      avg[i] += analogRead(pins[i]); // stores voltage of a cell
    }
    delay(15);
  }

  for (int i = 0; i < pinCnt; i++) measured[i] = ((avg[i] / runAvgCnt) * convert * constant[i] + scale[i]);

  for (int i = pinCnt - 1; i > 0; i--) measured[i] = measured[i] - measured[i-1]; // Calculating individual cell voltages 
  
  for (int i = 0; i < pinCnt; i++) {
    Serial.print("Run Average Cell "); Serial.print(i + 1); Serial.print(" "); Serial.print(pins[i]); Serial.print(": "); Serial.println(measured[i], 2);
  }
  Serial.println("\n\n\n");

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

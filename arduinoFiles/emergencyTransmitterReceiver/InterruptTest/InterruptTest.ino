
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Display Constants and Global Object Creation ~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1   // Reset pin # (sharing Arduino reset pin as it is -1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PIN_EMERGENCY_SWITCH 1 /* The pin that the emergency switch is connected to */
volatile byte EmergencyState;
volatile byte StateChange = true; /* Set to true so the display is updated the first go around*/

// =====================================================================================================
void setup() {
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Serial Monitor Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Serial.begin(9600);
  while (!Serial.available());
  Serial.println("The serial monitor has been established");

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Display Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /* Print the success or failure of the serial monitor initialzition in the serial monitor */
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) Serial.println(F("SSD1306 allocation failed"));
  else Serial.println(F("SSD1306 allocation succeeded"));
  display.display(); /* Update the output on the display */
  delay(2000); /* Wait for 2 seconds to ensure that the display has been initialized */

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ E-Switch Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  /* Configure the pin that the switch is connected to to input - hardware pullup installed on board*/
  pinMode(PIN_EMERGENCY_SWITCH, INPUT);
  /* Set the emergencyState variable to the state of the emergency switch;s input pin */
  EmergencyState = digitalRead(PIN_EMERGENCY_SWITCH);
  /* Enable the ISR for the emergency stop button switch */
  attachInterrupt(digitalPinToInterrupt(PIN_EMERGENCY_SWITCH), ISR_EmergencyStateChange, CHANGE);

}
// =====================================================================================================
void loop() {
  if (StateChange == true) {
    StateChange = false;
    updateDisplay();
  }
}

// =====================================================================================================
void ISR_EmergencyStateChange() {
  // Debouncing:
  /* If the new value does not match the old value, there might have been a state change */
  if (EmergencyState != digitalRead(PIN_EMERGENCY_SWITCH)) {
    /* delayMicroseconds() Does not use an ISR timer so it works inside of another ISR */
    delayMicroseconds(50000);
    /* If the new value still does not match the old value, there was a state change */
    if (EmergencyState != digitalRead(PIN_EMERGENCY_SWITCH)) {
      EmergencyState = !EmergencyState; /* Update the EmergencyState variable */
      StateChange = true; /* Set the emergency state to be updated in the loop */
    }
  }
}

// =====================================================================================================
void updateDisplay() {
  display.clearDisplay(); /* Clear the display */
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (digitalRead(PIN_EMERGENCY_SWITCH) == HIGH) {
    display.println("Emergency");
    Serial.println("Emergency Mode Triggered");
  } else {
    display.println("Normal");
    Serial.println("Normal Operation");
  }
  display.display(); /* Update the display */
}

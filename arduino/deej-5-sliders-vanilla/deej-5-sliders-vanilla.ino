const int NUM_SLIDERS = 6;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A6, A7};
//change last 2 slider to A6&A7 since the A4&A5 are taken by I2C on Seeeduino Lotus;
int analogSliderValues[NUM_SLIDERS];

//add LCD library of 16x2 LCD shield;
#include "rgb_lcd.h"
rgb_lcd lcd;

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

//initialise the lcd screen;
  lcd.begin(16,2);
  
  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug

  lcd.setCursor(0,0);
  lcd.print("1:");
  lcd.setCursor(2,0);
  lcd.print("Master");
  lcd.setCursor(0,1);
  lcd.print("2:");
  lcd.setCursor(3,1);
  lcd.print("Chrome");
  
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

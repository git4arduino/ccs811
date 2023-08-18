/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | https://linktr.ee/pixeledi
CCS811 Sensor | V1.0 | 10.2023
*/

#include <Wire.h>
#include "Adafruit_CCS811.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "grafics.h"

Adafruit_CCS811 ccs;

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
unsigned long previousMillis = 0;
uint16_t eco2, etvoc;

void showSensorValues() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  // eco2 data.
  display.setCursor(0, 2);
  display.setTextSize(2);
  display.print("eco2");

  display.setCursor(10, 35);
  display.setTextSize(1);
  display.print(eco2);
  display.print(" ppm ");

  display.drawLine(SCREEN_WIDTH / 2, 30, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);

  byte halfscreen = SCREEN_WIDTH / 2;
  display.setTextSize(2);
  display.setCursor(halfscreen, 2);
  display.print("etvoc");

  display.setCursor(halfscreen + 20, 35);
  display.setTextSize(1);
  display.print(etvoc);
  display.print(" ppb ");

  display.display();
}

void getSensorValues() {

  if (ccs.available()) {
    if (!ccs.readData()) {
      //globals
      eco2 = ccs.geteCO2();
      etvoc = ccs.getTVOC();
    } else {
      Serial.println("ERROR!");
      while (1)
        ;
    }
  }
}

void setup() {

  Serial.begin(115200);
  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  Serial.println("loading image");
  writeTextAndGrafic("C02", "Sensor", mylogo);  // function in grafics.h

  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1)
      ;
  }

  // Wait for the sensor to be ready could be a few seconds
  while (!ccs.available())
    ;

  //show additional 5 sec the logo
  delay(5000);
  Serial.println("setup finished");
}

void loop() {


  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000) {
    previousMillis = currentMillis;
    getSensorValues();
    showSensorValues();
  }
}
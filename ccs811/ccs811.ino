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

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

void setup() {

  Serial.begin(115200);

  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1)
      ;
  }

  // Wait for the sensor to be ready
  while (!ccs.available())
    ;
}

void loop() {
  if (ccs.available()) {
    if (!ccs.readData()) {
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    } else {
      Serial.println("ERROR!");
      while (1)
        ;
    }
  }
  delay(500);
}
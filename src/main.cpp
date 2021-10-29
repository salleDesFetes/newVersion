#include <Arduino.h>
#include <M5Stack.h>
#include "clock.h"
#include <time.h>
#include "bagTower.h"

#include "Adafruit_SGP30.h"

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.print("Hello world");
  printLocalTime();
  setupClock();
  setupAPI();
}

void loop() {
  printTime();
  loopAPI();
}

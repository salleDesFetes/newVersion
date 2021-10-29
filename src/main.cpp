#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <time.h>

#include "clock.h"
#include "bagTower.h"
#include "Adafruit_SGP30.h"


Adafruit_SGP30 sgp;

void header(const char *string, uint16_t color)
{
    M5.Lcd.fillScreen(color);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.fillRect(0, 0, 320, 30, TFT_BLACK);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(string, 160, 3, 4); 
}

void setup() {
  // Serial.print(analogRead(21));
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(115200);
  // header("RECUPERATION DONNEES",TFT_BLACK);
  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  } 

  M5.Lcd.drawString("TVOC:", 50, 40, 4);
  M5.Lcd.drawString("eCO2:", 50, 80, 4);
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
  M5.Lcd.drawString("Initialization...", 140, 120, 4);
  M5.Lcd.fillRect(0, 120, 300, 30, TFT_BLACK);

  for(int i = 15; i > 0; i--) {
      M5.Lcd.clear();    
      M5.Lcd.fillRect(198, 120, 40, 20, TFT_BLACK);
      M5.Lcd.drawNumber(i, 20, 120, 4);
      M5.Lcd.progressBar(0, 0, 10, TFT_HEIGHT, (100 / 15) * i);
      delay(1000);
  }

  Serial.println("end for");
  printLocalTime();
  setupClock();
  setupAPI();

  Serial.println("End Setup");
}


void loop() {


  printTime();

  M5.Lcd.fillRect(0, 120, 300, 30, TFT_BLACK);

  if (! sgp.IAQmeasure()) {
    Serial.println("raté");
    return;
  }

  M5.Lcd.fillRect(100, 40, 220, 90, TFT_BLACK);
  M5.Lcd.drawNumber(sgp.TVOC, 120, 40 , 4);
  M5.Lcd.drawString("temperature", 200, 40, 4);
  M5.Lcd.drawNumber(sgp.eCO2, 120, 80, 4);
  M5.Lcd.drawString("le co2 :", 200, 80, 4);
  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
  loopAPI(sgp.TVOC);
  delay(1000);
}



void printTime()
{
  delay(1000);
  printLocalTime();
}


void setupClock() {
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
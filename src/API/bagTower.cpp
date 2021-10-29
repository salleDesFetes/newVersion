#include <Arduino.h>
#include <ArduinoJson.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include "bagTower.h"

const char* ssid = "HUAWEI P smart";
const char* password = "MooMoomin";

unsigned int value = 0;

// Domain Name with full URL Path for HTTP POST Request
const char* server = "https://api.bagtower.bag-era.fr/prod/logs";
String my_Api_key = "MS9lx8JHdq1upJC6BTx0BD6wRwjBikX3dK5KFX19";
unsigned long last_time = 0;
unsigned long timer_delay = 10000;
// allocate the memory for the document
StaticJsonDocument<250> doc;
StaticJsonDocument<250> docData;
// create an empty array
JsonObject postLogs = doc.to<JsonObject>();
JsonObject data = docData.to<JsonObject>();
void setupAPI() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI…");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("After 10 seconds the first reading will be displayed");
  //initialize a random number
  randomSeed(analogRead(23));
}
void loopAPI(int value) {
  //Send an HTTP POST request every 10 seconds
  if ((millis() - last_time) > timer_delay) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      http.begin(server);
      http.addHeader( "x-api-key" , my_Api_key );
      http.addHeader("Content-Type", "application/json");
      // Data to send with HTTP POST
      // todo :
      // construct jsonObject
      // transform jsonObject into string

      data["id"] = "1";
      data["type"] = "string";
      data["val"] = value;
      postLogs["unixTimestamp"] = 0;
      postLogs.createNestedArray("data");
      postLogs["data"].add(data);
      postLogs["UTCTimestamp"] = "timestampTest";
      postLogs["deviceId"] = "6f34c9b0-1791-1:fb673630-3658-11ec-9";
      String payload;
      serializeJson(doc, payload);
      Serial.println(payload);
      // Send HTTP POST request
      int httpResponseCode = http.POST(payload);
      Serial.print("HTTP Response code is: ");
      Serial.println(httpResponseCode);
      http.end();
    }
    else {
      Serial.println("WiFi is Disconnected!");
    }
    delay(600000);
    last_time = millis();
  }
}
/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core sample source code
*                            M5Core 
* Visit the website for more information：https://docs.m5stack.com/en/core/gray
* ：https://docs.m5stack.com/zh_CN/core/gray
*
* describe：PIR.  
* date：2021/8/11
*******************************************************************************
  Please connect to Port B(26、36),Human body detection using PIR Unit.
 
*/
// coucou
#include <M5Stack.h>

void setup() {
  M5.begin(); //Init M5Stack
  M5.Power.begin(); //Init power  
  M5.lcd.setTextSize(2);  //Set the text size to 2.  
  M5.Lcd.println("PIR example");
  M5.Lcd.setCursor(0, 25);  //Position the cursor at (0,25).  
  M5.Lcd.println("Status: \nValue: ");
  pinMode(22, INPUT); //Set pin 36 to input mode.  
}

void loop() {
  M5.Lcd.fillRect(90,25,180,50,BLACK);  //Draw a black rectangle 180 by 50 at (90,25)
  if(digitalRead(22)==1){ //If pin 36 reads a value of 1.  
    M5.Lcd.setCursor(95, 25);M5.Lcd.print("Sensing");
    M5.Lcd.setCursor(95, 45);M5.Lcd.print("1");
  }
  else{
    M5.Lcd.setCursor(95, 25);M5.Lcd.print("Not Sensed");
    M5.Lcd.setCursor(95, 45);M5.Lcd.print("0");
  }
  delay(500);
}
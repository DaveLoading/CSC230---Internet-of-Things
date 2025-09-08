
#include <M5Core2.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>

#include "secrets.h"
#include <WiFi.h>
/*
Lab 8.1
David Shamas
July 7th 2025
david.loadingexperiment@gmail.com

*/


void setup() {
  Serial.begin(115200);
  M5.begin();
  
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.print("connecting ");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay (500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP() );

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("Screen_Color", "Black");
  
}

void loop() {
  String fireStatus = Firebase.getString("Screen_Color");
  if (fireStatus == "Black") {
    Serial.println("Screen black");
    M5.Lcd.fillScreen(BLACK);
  } else if (fireStatus == "Red") {
    Serial.println("Red");
    M5.Lcd.fillScreen(RED);
  } else if (fireStatus == "Green") {
    Serial.println("Green");
    M5.Lcd.fillScreen(GREEN);
  }else {
     Serial.println("non viable color");
  }


}

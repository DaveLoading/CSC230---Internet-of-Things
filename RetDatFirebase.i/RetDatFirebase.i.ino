/*
  Retrieve data on google firbase
  David Shamas
  July 15th 2025
  david.loadingexperiment@gmail.com
*/

#include <M5Core2.h>

#include <Firebase_ESP_Client.h>

#include "secrets.h"
#include <WiFi.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

//firebase data object 
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//Tracks the last time data was sent or retrieved
unsigned long sendDataPrevMillis = 0;
//Variables to holde Firebase values
int intValue;
float floatValue;
//Show if sign-up was successful
bool signupOK = false;


void setup() {
  Serial.begin(115200);
  M5.begin();
  
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.print("Connecting to Wi-Fi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP() );
  //Assign the api key required
  config.api_key = API_KEY;
  //Assign the RTB URL required
  config.database_url = DATABASE_URL;

  //Sign up
  if (Firebase.signUp(&config, &auth, "","")){
    Serial.println("ok");
    signupOK = true;
  }
    else {
      // Sign-up failed — print the error message
      Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }
    //Assign the callback function for the long running token generation task
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
  }


void loop() {
  /*Check Firebase every 30s*/
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 30000 || sendDataPrevMillis ==0)){
    sendDataPrevMillis = millis();

    // Clear the screen for fresh data
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE);


    // Retrieve int from /test/int 
    if (Firebase.RTDB.getInt(&fbdo, "/test/int")){
      //Make sure data is int
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData(); //store it in intValue
        Serial.println(intValue); //print the int 

        //set text size
        M5.Lcd.setTextSize(2);
        //center text 
        M5.Lcd.setCursor(50,30);
        //Display int on screen
        M5.Lcd.println("Int Value:");
         //set text size
        M5.Lcd.setTextSize(2);
        //center text 
        M5.Lcd.setCursor(190,30);
        //print int value
        M5.Lcd.println(intValue);
      }
    }

    else {
      //Shows the reason it failed
      Serial.println(fbdo.errorReason());

        //set text size
        M5.Lcd.setTextSize(2);
        //center text 
        M5.Lcd.setCursor(100,50);
        //Display int failure on screen
        M5.Lcd.println("Int Failed");
      
    }

    // Retrieve float from /test/float 
    if (Firebase.RTDB.getFloat(&fbdo, "/test/float")){
      //Make sure data is float
      if (fbdo.dataType() == "float") {
     floatValue = fbdo.floatData(); //store it in floatValue
        Serial.println(floatValue); //print the float 

        //set text size
        M5.Lcd.setTextSize(2);
        //center text 
        M5.Lcd.setCursor(50,50);
        //Display float on screen
        M5.Lcd.println("Float Value:");
         //set text size
        M5.Lcd.setTextSize(2);
        //center text 
        M5.Lcd.setCursor(220,50);
        //print float value
        M5.Lcd.println(floatValue);
      }
    }
    else {
      //Shows the reason it failed
      Serial.println(fbdo.errorReason());
      
      //set text size
        M5.Lcd.setTextSize(2);
        //center text 
        M5.Lcd.setCursor(100,50);
      //Display float failure on screen
        M5.Lcd.println("Float Failed");
    }
  }
}

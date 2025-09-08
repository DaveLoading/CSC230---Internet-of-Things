/*
  Recording data on google firebase
  David Shamas
  July 14th 2025
  david.loadingexperiment@gmail.com
*/

#include <M5Core2.h>

#include <Arduino.h>

#include <Firebase_ESP_Client.h>

#include "secrets.h"
#include <WiFi.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

//firebase data object 
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


void setup() {
  Serial.begin(115200);
  M5.begin();
  
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.print("connecting ");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
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
    // chatgpt recommended line this line sets the signupOk to be true so it will connect 
    //otherwise it will see the connection as false  
    signupOK = true; 
  }
    else {
      Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }
    //Assign the callback function for the long running token generation task
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
  }


void loop() {
  /*Check if Firebase is ready, sign-up succeeded, and 15s has passed since last upload*/
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis ==0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
      //confirms success writing to firebas
      Serial.println("PASSED");
      //shows the exact path written in the database
      Serial.println("PATH: " + fbdo.dataPath());
      //Shows the type of data written 
      Serial.println("TYPE: " + fbdo.dataPath());
    }
    else {
      //shows that it failed
      Serial.println("FAILED");
      //tells you why it failed
      Serial.println("REASON: " + fbdo.dataPath());
    }
    count++; //Adds 1 to the count each time the loop runs

    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
      //confirms success writing to firebas
      Serial.println("PASSED");
       //shows the exact path written in the database
      Serial.println("PATH: " + fbdo.dataPath());
      //Shows the type of data written 
      Serial.println("TYPE: " + fbdo.dataPath());
    }
    else {
      //shows that it failed
      Serial.println("FAILED");
       //tells you why it failed
      Serial.println("REASON: " + fbdo.dataPath());
    }
  }
}

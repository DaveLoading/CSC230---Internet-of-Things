#include <M5Core2.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>


const char* ssid = "Frontierg5552";
const char* password = "1859115180";

//Your Domain name with URL path or IP address with path 
String openWeatherMapApiKey = "9ea881cd9073ee70f5711e6757c55bd0";


//Replace with your country code and city
String city = "Tempe";
String countryCode = "US";

//The Default Timer is set to 10 seconds for Testing Purposes
//For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
//Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
//Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  //Your Domain name with URL oath or IP address with path
  http.begin(client, serverName);

  //Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  //Free resources
  http.end();

  return payload;
}

void setup() {
  Serial.begin(115200);
  //start M5
  M5.begin();

  WiFi.begin(ssid,password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
  //clear lcd screen
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
        city = "Tempe";
    } else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
        city = "Hawthorne";
    } else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
        city = "Manhattan";
    } 
  
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED) {
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" +city + "," + countryCode + "&units=imperial&APPID=" + openWeatherMapApiKey;

      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);

      //JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failerd!");
        return;
      }

      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("Temperature: ");
      Serial.println(myObject["main"]["temp"]);
      Serial.print("Pressure: ");
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("Humidity: ");
      Serial.println(myObject["main"]["humidity"]);
      Serial.print("Wind Speed: ");
      Serial.println(myObject["wind"]["speed"]);
      
      //convert K to F 
      float tempF = double(myObject["main"]["temp"]);
      Serial.println(tempF);
      
      //display city name and country symbol on screen 
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print("City: ");
      M5.Lcd.println(city);
      M5.Lcd.print("  Country: ");
      M5.Lcd.println(countryCode);
    
      //setup to display temp and humidity on screen
      M5.Lcd.print("Temp: ");
      M5.Lcd.println(tempF);
      M5.Lcd.print("  Humidity: ");
      M5.Lcd.println(myObject["main"]["humidity"]);
    }
    
    else{
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

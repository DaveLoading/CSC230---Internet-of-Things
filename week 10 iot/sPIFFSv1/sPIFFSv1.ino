#include <SPIFFS.h>
#include <M5Core2.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);
  //SPIFFS startup
  if (SPIFFS.begin(true)) {
    Serial.println("SPIFFS mounted successfully.");
  } else {
    Serial.println("SPIFFS mount failed. Check your filesystem.");
  }
  M5.begin();
  M5.Lcd.fillScreen(RED);
  splashScreen ();
}

void loop() {

 
}

void splashScreen (){
   Serial.println("SplashScreen()");
   M5.Lcd.drawJpgFile(SPIFFS, "/imgv1.jpeg", 40 ,0);
   M5.Lcd.setTextSize(2);
   M5.Lcd.setCursor(20,220);
   M5.Lcd.print("Press botton to continue");
   while(done == 0){
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000,200) || M5.Btn.wasReleased() || M5.BtnB.pressedFor(1000,200)
    || M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000,200)) {
    done = 1;
   }
  }
  

/* determination of voltage for resistance det
  David Shamas 
  June 30th 2025
  david.loadingexperiment@gmail.com

*/
#include <M5Core2.h>

//variable declare 
//voltVal is based on 10 bit (0-1023)
int voltVAl = 0;
//actVolt is the actual determined voltage of the voltage provider
float actVolt = 0.0f;


void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.print("volt det begin");
  pinMode(35, INPUT);
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.print("Begin Volt collect");
  delay(5000);
}

void loop() {
  voltVAl = analogRead(35);
  Serial.print("pin 35 value = ");
  Serial.print(voltVAl);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,0,2);
  M5.Lcd.println("Voltage divider value");
  M5.Lcd.print(voltVAl);
  delay(1000);
}

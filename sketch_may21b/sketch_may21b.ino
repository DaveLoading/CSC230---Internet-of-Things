#include <M5Core2.h>

  /*/ First program on the MN5Core2
      David Shamas
      21May2025
      david.loadingexperiment@gmail.com

      the library for M5Core2 really stinks!!

  
  */



void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Hello World");
    
    //M5.Lcd.setTextSize(10);  // Set the font size. 
}


void loop() {
  // put your main code here, to run repeatedly:

}

#include <M5Core2.h>
/* Lab 6.1 
  David Shamas
  July 9th 2025
  david.loadingexperiment@gmail.com

*/

//Pin
const int adcPin = 35;

//adc stands for analog to digital converter 
//Takes an analog signal and convert it to digital between 10-4095
float adcVal = 0;
//Using float for a decimal and this will tell the voltage value
float voltVal =0;
//Max adc Value
float adcMax = 4095.0;
//max voltage
float voltMax = 3.3;

//Resistor Value
float R1 = 35100;
float R2, T, Tc, Tf;

//Formula's 
const float c1 = 1.009249522e-03;
const float c2 = 2.378405444e-04;
const float c3 = 2.019202697e-07;

void setup() {
  //start moniter
  Serial.begin(9600);
  //start library
  M5.begin();
  //set up pin
  pinMode(adcPin, INPUT);
  //screen black
  M5.Lcd.fillScreen(BLACK);
  //make text size bigger
  M5.Lcd.setTextSize(3);
}

void loop() {
  //analog value
  adcVal = analogRead(adcPin);
  //thermistor calculations
  R2 = R1 * ((adcMax - adcVal) / adcVal);
  
  // Convert resistance to temperature using formulas
  float logR2 = log(R2);
  T = 1.0 / (c1 + c2 * logR2 + c3 * pow(logR2, 3));
  // Celsius
  Tc = T - 273.15;             
  // Fahrenheit
  Tf = Tc * 9.0 / 5.0 + 32.0;  
  
  Serial.println(T);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.printf("ADC VAL: %.2f", adcVal);

  //ADC to voltage
  voltVal = (adcVal/ adcMax) * voltMax;
  M5.Lcd.setCursor(0,40);
  M5.Lcd.printf("ADC Voltage: %.2f",voltVal);

  M5.Lcd.setCursor(0,70);
  M5.Lcd.printf("Max Voltage: %.2f", voltMax);

  M5.Lcd.setCursor(0,100);
  M5.Lcd.printf("ADC Max : %.2f", adcMax);
  
  M5.Lcd.setCursor(0,130);
  M5.Lcd.print("Temp: ");
  //Fahrenheit
  M5.Lcd.print(Tf);
  M5.Lcd.print(" F /  ");
  // Celsius
  M5.Lcd.print(Tc);
  M5.Lcd.print(" C");

  delay(200);
}

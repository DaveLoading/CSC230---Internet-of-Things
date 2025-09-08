#include <M5Core2.h>
/* read voltage and then determine resistance 
  David Shamas
  July 1st 2025
  david.loadingexperiment@gmail.com

*/
//adc stands for analog to digital converter 
//Takes an analog signal and convert it to digital between 10-4095
int adcVal = 0;
//Using float for a decimal and this will tell the voltage value
float voltVal =0.0f;
//Max adc Value
float adcMax = 4095.0;
//Stands for Voltage Common Collector
float vcc = 3.3;
//Thermistor Value
float thermVal = 0.0f;
//constant resistor
float R2 = 35100;
int adcPin = 35
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(9600);
  M5.begin();
  pinMode(adcPin, INPUT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(10,10);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Display Test!");
  delay(1000);
}

void loop() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10,10);
  adcVal = analogRead(adcPin);
  // r2 = r1 * (adcMax / (adcMax - adcVal))
  R2 = R1 * (adcMax / (adcVal - 1.0))
  logR2 = log(R2);
  T = (1.0 / (c1 +c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc *9.0)/ 5.0 + 32.0;
  Serial.println(T);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.printf("ADC VAL: %.2f", adcVal);

  voltVal = (adcVal/ adcMax) * voltMax;
  M5.Lcd.setCursor(0,30);
  M5.Lcd.print("ADC Voltsge: %.2f",voltVal);

  M5.Lcd.setCursor(0,50);
  M5.Lcd.print("Max Voltage: %.2f", voltMax);

  M5.Lcd.setCursor(0,70);
  M5.Lcd.print("ADC Max : %.2f", adcMax);
  
  M5.Lcd.setCursor(0,90);
  M5.Lcd.print("Temp: ");
  M5.Lcd.print(Tf);
  M5.Lcd.print(" F;  ");
  M5.Lcd.print(Tc);
  M5.Lcd.print(" C");

  delay(200);
  //Give us percentage of the max then give us our volt value
  /*voltVal = (adcVal/adcMax)*vcc;
  M5.Lcd.setCursor(10,50);
  M5.Lcd.print(voltVal);*/
  thermVal = (3.3*R2/voltVal)-R2;
  M5.Lcd.setCursor(10,90);
  M5.Lcd.print(thermVal);
  delay(1000);
}

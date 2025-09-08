/*
*******************************************************************************
Lab 4.1 M5Core2 IMU Sensord
    David Shamas
    June 17th 2025
    david.loadingexperiment@gmail.com
*******************************************************************************
*/
#include <M5Core2.h>

float accX = 0.0F;  // Define variables for storing inertial sensor data
float accY = 0.0F;  
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float maxX = 0.0F;
float maxY = 0.0F;
float maxZ = 0.0F;

//maxVector value
float maxVec = 0.0F;
float tmpVec = 0.0F;

//to make calculations easier 
float xSq = 0.0F;
float ySq = 0.0F;
float zSq = 0.0F;

//flag to prevent repeated blinking
bool blinkTriggered = false;

/* After M5Core2 is started or reset
the program in the setUp () function will be run, and this part will only be run
once. */
void setup() {
    M5.begin();                // Init M5Core.  
    M5.IMU.Init();             // Init IMU sensor.  
    M5.Lcd.fillScreen(BLACK);  // Set the screen background color to black.
    M5.Lcd.setTextColor( GREEN,  BLACK);  // Sets the foreground color and background color of the displayed text. 
    M5.Lcd.setTextSize(2);  // Set the font size. 
}

void loop() {
     //Add button to clear max data 
     //M5.update() check button data
     M5.update(); 
    
    // Stores the triaxial gyroscope data of the inertial sensor to the relevant variable 
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAccelData( &accX, &accY, &accZ);  // Stores the triaxial accelerometer. 
    

    /* The M5Core screen is 320x240 pixels, starting at the top left corner of
    the screen (0,0). gyroscope output related M5Core2
    320x240, (0,0)*/
    // gyroscope output related.  
    M5.Lcd.setCursor(0, 20);  // Move the cursor position to (x,y).
    M5.Lcd.printf("gyroX,  gyroY, gyroZ");  // Screen printingformatted string.
    M5.Lcd.setCursor(0, 42);
    M5.Lcd.printf("%6.2f %6.2f%6.2f o/s", gyroX, gyroY, gyroZ);

    // Accelerometer output is related
    M5.Lcd.setCursor(0, 70);
    M5.Lcd.printf("accX,   accY,  accZ");
    M5.Lcd.setCursor(0, 92);
    M5.Lcd.printf("%5.2f  %5.2f  %5.2f G", accX, accY, accZ);



    //make sure max is really maxd
    if(accX > maxX){
        maxX = accX;
    }

     if(accY > maxY){
        maxY = accY;
     }

     if(accZ > maxZ){
        maxZ = accZ;
     }

    // Pose output is related
    M5.Lcd.setCursor(0, 120);
    M5.Lcd.printf("maxX,  maxY,  maxZ");
    M5.Lcd.setCursor(0, 142);
    M5.Lcd.printf("%5.2f  %5.2f  %5.2f deg", maxX, maxY, maxZ);

    // maxVector stuff 
    //get X, Y, and Z squared
    xSq = sq(accX);
    ySq = sq(accY);
    zSq = sq(accZ);

    tmpVec = sqrt(xSq + ySq + zSq);
    if (tmpVec > maxZ) {
        maxVec = tmpVec;
    }

    M5.Lcd.setCursor(0, 175);
    M5.Lcd.printf("MaxVector : %.2f G", maxVec);

    //clear max value from button A  
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    maxX = 0.0F; // Define variable for storing inertial sensor data 
    maxY = 0.0F;
    maxZ = 0.0F;
    maxVec = 0.0F;

    } 

    //Drop Detection and screen blink
    // If a free fall is detected (accZ ~ 0), trigger blink
    if (accZ < 0.2 && !blinkTriggered) {
    blinkTriggered = true;

    // Blink screen RED/WHITE 5x (500ms rate = 2Hz)
    for (int i = 0; i < 5; i++) {
      //turn screen red
      M5.Lcd.fillScreen(RED);
     //half of 500
      delay(250);
      //turn screen white
      M5.Lcd.fillScreen(WHITE);
      //half of 500
      delay(250);
    }

    // Restore screen
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(GREEN, BLACK);
  }

  // Reset trigger when stable again
  if (accZ > 0.8) {
    // Ready to detect next drop
    blinkTriggered = false;
  }

    delay(100);  // Delay 10ms. 
    
     
}
/* Lab 3.1: Working with Displays and Touchscreen Buttons
    David Shamas
    June 2nd 2025 
    david.loadingexperiment@gmail.com
*/
#include <M5Core2.h>

// global variable
String myName = "David Shamas";
long randNum = 0;

void setup() {
  //we need to start the library to use it 
  M5.begin();

  //setting randNum seed
  randomSeed(analogRead(0));

  //color screen red
  M5.Lcd.fillScreen(RED);

  //delay 1 second 
  delay(1000);
 
  //color screen white 
  M5.Lcd.fillScreen(WHITE);

  //delay 1 second
  delay(1000);

  //color screen blue
  M5.Lcd.fillScreen(BLUE);

  //delay 1 second 
  delay(1000);

  //color screen black
  M5.Lcd.fillScreen(BLACK);
  
  //set curser to 20,20
  M5.Lcd.setCursor(20,20);
        
  //set text size to 2
  M5.Lcd.setTextSize(2);

  //Text Color
  M5.Lcd.setTextColor(WHITE);

  //write name
  M5.Lcd.print("David Shamas");


  //delay 1 second 
  delay(1000);
  //changing to prt 2 
  //changing screen to white 
  M5.Lcd.fillScreen(WHITE);
  //adding part 2 text 
  //set text size to 2
  M5.Lcd.setTextSize(2);
  //set curser to center
  M5.Lcd.setCursor(100,100);
  //Text Color
  M5.Lcd.setTextColor(BLACK);
  //write Part 2
  M5.Lcd.print("Part 2");
  //delay 1 second 
  delay(1000);


  //part 2 starting changing screen to white 
  M5.Lcd.fillScreen(WHITE);
  //Text Color
  M5.Lcd.setTextColor(MAGENTA);
  //set text size to be as big as possible on one line 
  M5.Lcd.setTextSize(3);
  //set curser to be middle and center
  M5.Lcd.setCursor(70,100);
  //write name
  M5.Lcd.printf("David Shamas");


//delay 1 second 
  delay(1000);
  //changing to prt 3 
  //changing screen to white 
  M5.Lcd.fillScreen(WHITE);
  //adding part 2 text 
  //set text size to 2
  M5.Lcd.setTextSize(2);
  //set curser to center
  M5.Lcd.setCursor(100,100);
  //Text Color
  M5.Lcd.setTextColor(BLACK);
  //write Part 3
  M5.Lcd.printf("Part 3");
  //delay 1 second 
  delay(1000);


  //set screen color 
  M5.Lcd.fillScreen(PURPLE);
  //set to be in the center 
  M5.Lcd.setCursor(50,100);
  //set text size 
  M5.Lcd.setTextSize(2);     
  //set text color
  M5.Lcd.setTextColor(WHITE , PURPLE); 
  //print text
  M5.Lcd.print("Loading Experiment");



}

void loop() {
  //setting up the buttons
  
  M5.update();
  //setting up the first button function
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    
    //screen color
    M5.Lcd.fillScreen(PURPLE);
    //centering text
    M5.Lcd.setCursor(50,100);
    //text size
    M5.Lcd.setTextSize(3);     
    //text color
    M5.Lcd.setTextColor(YELLOW), PURPLE; 
    //what the text is printing 
    M5.Lcd.print(myName);
 
    //setting up second button function
    }  else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) { 

    //screen color
    M5.Lcd.fillScreen(BLUE);
    //centering text
    M5.Lcd.setCursor(50,100);
    //text size
    M5.Lcd.setTextSize(2);     
    //text color
    M5.Lcd.setTextColor(WHITE , BLUE); 
    //what text will say 
    M5.Lcd.print("Loading Experiment");

      //setting up third button function
    } else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) { 
       //Setting up random number generator 
       randNum = random(1,4);
       //setting up first option 
       if(randNum == 1){
        //screen color
       M5.Lcd.fillScreen(YELLOW);
       //center the random number
       M5.Lcd.setCursor(50,100);
       //set text size
       M5.Lcd.setTextSize(3);     
       //set text color
       M5.Lcd.setTextColor(RED , YELLOW); 
       //write the random number 
       M5.Lcd.print(randNum);

       //setting up second option
       } else if (randNum ==2) {
         //screen color
       M5.Lcd.fillScreen(BLACK);
       //center the random number
       M5.Lcd.setCursor(50,100);
       //set text size
       M5.Lcd.setTextSize(3);     
       //set text color
       M5.Lcd.setTextColor(MAGENTA , BLACK); 
       //write the random number 
       M5.Lcd.print(randNum);
       //setting up third option 
       } else if (randNum ==3){
       //screen color
       M5.Lcd.fillScreen(BLUE);
       //center the random number
       M5.Lcd.setCursor(50,100);
       //set text size
       M5.Lcd.setTextSize(3);     
       //set text color
       M5.Lcd.setTextColor(WHITE, BLUE); 
       //write the random number 
       M5.Lcd.print(randNum);
       }
}}

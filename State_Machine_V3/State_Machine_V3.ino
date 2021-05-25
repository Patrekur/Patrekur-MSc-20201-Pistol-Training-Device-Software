
// include the library code:
#include <CircularBuffer.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// initialize the lyquidChrystal library with the numbers of the interface pins
#define REDLITE 2  // pin 16
#define GREENLITE 3 // pin 17
#define BLUELITE 4  // pin 18
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);
// iamge ->LCD-RedBoard, 4-7, 6-8, 11-9, 12-10, 13-11, 14-12, 16-3, 17-5, 18-6
int brightness = 255; // brightness of RGB LCD
// LCDrows is used in void textToScreen();
int LCDrows = 20; // 20 for 4x20 LCD, 16 for 2x16 LCD

//the buttons
const int exitButtonPin = A4;
const int okButtonPin = A5;
const int backButtonPin = A3;
const int nextButtonPin = A2;
//these variables track the state of the buttons, low if not pressed, high if pressed
int exitButtonState = LOW; 
int okButtonState = LOW; 

int nextButtonState = LOW;
int backButtonState = LOW;

// For debouncing the buttons
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 250;    // the debounce time; increase if the output flickers
int buttonState;

// The red and green LEDs for the targets - will become MOSFE-Transistors
const int greenLedPin = 12;
const int redLedPin = 11;

// for stateMachines
int state = 0; 
unsigned long pressTime = 0; // how long since a button has been pressed
bool isMenu = true;
bool isSports = false;
bool isSettings = false;
bool isUnallocated = false;
bool okAccept = false;
bool exitAccept = false;
bool backNextAccept = false;
bool buttonStateChange = false;


// LIFO buffer
// https://github.com/rlogiacco/CircularBuffer#declare-and-initialize
CircularBuffer<char,20> stateHistory; // buffer capacity is 20 characters
// I doubt the machines go more than 4 states deep.
/* buffer.push(0);  // [0]
   buffer.push(5);  // [0,5]
   buffer.pop(); // [0] returns 5
   buffer.pop(); // [] returns 0    */


//---------------- external function declarat-----------ion ------
void monitorButtonPress();
void setLiquidCrystalBacklight(uint8_t r, uint8_t g, uint8_t b);
void menuMachine();
//////////////////////////////////////////////////// void setup begins ////////////////////////////////////////////////////
void setup() {
  // set up the LCD's number of rows and columns:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  
  lcd.print("Welcome! to:");
  lcd.setCursor(0, 1);
  lcd.print("State_Machine_V3");

  //set the mode of the pins...
  // For the Red and Green lights
  pinMode(greenLedPin, OUTPUT);// declare the ledPin as an OUTPUT
  pinMode(redLedPin, OUTPUT);
  // For buttons
  pinMode(exitButtonPin, INPUT);
  pinMode(okButtonPin, INPUT);
  pinMode(backButtonPin, INPUT);
  pinMode(nextButtonPin, INPUT);
  // For LyquidChrystal
  pinMode(REDLITE, OUTPUT);
  pinMode(GREENLITE, OUTPUT);
  pinMode(BLUELITE, OUTPUT);

  // Set the brightness and backlight of the LCD
  brightness = 154;
  setLiquidCrystalBacklight(154, 154, 154);

  // initialize serial communication:
  Serial.begin(9600);

  stateHistory.push('B'); // -------- history shows where beginning is
  stateHistory.push('B'); // -------- history shows where beginning is
  stateHistory.push('B'); // -------- history shows where beginning is
  
  delay(2500); // There is a delay here !!!!!!!!!!!!
  lcd.clear();
//  textOnScreen(0,0,"Button:");
}
//////////////////////////////////////////////////// void setup ends ////////////////////////////////////////////////////

//////////////////////////////////////////////////// void loop begins ////////////////////////////////////////////////////
void loop() {
  monitorButtonPress();

  menuMachine();
//  buttonFunctionTester();
}//close void loop
//////////////////////////////////////////////////// void loop ends ///////////////////////////////////////////////////





void buttonFunctionTester(){
  textOnScreen(0,1,"");
  textOnScreen(0,0,"--ButtonTester--");
  while(onlyAllowRisingButton(backButtonPin, backButtonState)){
  textOnScreen(0,1,"   back pressed");
  }
  while(onlyAllowRisingButton(nextButtonPin, nextButtonState)){
    textOnScreen(0,1,"   next pressed");
  }
  while(onlyAllowRisingButton(okButtonPin, okButtonState)){
    textOnScreen(0,1,"     ok pressed");
  }
  while(onlyAllowRisingButton(exitButtonPin, exitButtonState)){
    textOnScreen(0,1,"   exit pressed");
  }
}


void textOnScreen(int c1, int c2, String text){
   /*textOnScreen(choose col, choose line, text){
   * Writes a msg to a line on the 16x2LCD
   * Replaces old msg with whitespace
   */
  String whiteSpace = "";
  int spaceLen = 0;
  spaceLen = LCDrows - text.length();
  for(int i = 1; i <= spaceLen; i++) {
    whiteSpace = whiteSpace + " ";  
  }
  text = text + whiteSpace;
  lcd.setCursor(c1, c2);
  lcd.print(text);
  
}

void setLiquidCrystalBacklight(uint8_t r, uint8_t g, uint8_t b) {
  // normalize the red LED - its brighter than the rest!
  r = map(r, 0, 255, 0, 100);
  g = map(g, 0, 255, 0, 150);

  r = map(r, 0, 255, 0, brightness);
  g = map(g, 0, 255, 0, brightness);
  b = map(b, 0, 255, 0, brightness);

  // common anode so invert!
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);
  Serial.print("R = "); Serial.print(r, DEC);
  Serial.print(" G = "); Serial.print(g, DEC);
  Serial.print(" B = "); Serial.println(b, DEC);
  analogWrite(REDLITE, r);
  analogWrite(GREENLITE, g);
  analogWrite(BLUELITE, b);
}

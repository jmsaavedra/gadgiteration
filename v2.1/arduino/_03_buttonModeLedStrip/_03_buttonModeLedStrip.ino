#include <Adafruit_NeoPixel.h>

/* still in progress */

//define all pins
#define buttonMode   2
#define buttonRange  4
#define ledStrip     6
#define ledMode      7
#define audioOut     8
#define ledOnboard   13
#define gadgitCircuitIn A0
#define humanCircuitIn  A1

//modes could be 0 - 8
uint8_t currentMode = 0; 

//current sensor value, regardless of human or not
int currentVal = 0; 

//setup neopixel strip
#define numStripLEDs 10//how many LEDs long
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numStripLEDs, ledStrip, NEO_GRB + NEO_KHZ800);

void setup(){
  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(ledMode, OUTPUT);
  pinMode(ledOnboard, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(57600);
}

void loop(){

  /* update buttons and mode LEDs */
  updateButtons();
  updateModeLeds();

  switch(currentMode){

  case 0: //--- REGULAR GADGIT MODE ---
    digitalWrite(ledOnboard, HIGH);
    currentVal = analogRead(gadgitCircuitIn);      
    //TODO: map currentVal to 0-1000 or 0-100 or something even

    colorWipe(strip.Color(0,255,200), currentVal); //color bar at blue/green

    Serial.print("GADGIT currentVal:\t");
    Serial.println(currentVal);

    break;

  case 1: //--- HUMAN CIRCUIT MODE ---
    digitalWrite(ledOnboard, LOW);
    currentVal = analogRead(humanCircuitIn);
    //TODO: map currentVal to 0-1000 or 0-100 or something even

    colorWipe(strip.Color(255,0,127), currentVal); //color bar at purple

    Serial.print("HUMAN currentVal:\t");
    Serial.println(currentVal);

    break;   
  }
}

void updateButtons(){
  /* check both buttons, set the global currentMode to
   * whichever button has last been pressed   */

  int currModeBut = digitalRead(buttonMode); 
  if(currModeBut) currentMode = 1;

  int currRangeBut = digitalRead(buttonRange); 
  if(currRangeBut) currentMode = 0;
}


void updateModeLeds(){
  /* check current mode and turn on correct modeLED */
  if(currentMode == 0)  digitalWrite(ledMode, HIGH);
  else digitalWrite(ledMode, LOW);
}








#include <Adafruit_NeoPixel.h>
#include "pitches.h"

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
#define sensorInput    A4

//modes could be 0 - 8
uint8_t currentMode = 0; 

//current sensor value, regardless of human or not
int currentVal = 0; 
int sensorState = 0;
int play = 0;

//setup neopixel strip
#define numStripLEDs 20//how many LEDs long
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numStripLEDs, ledStrip, NEO_GRB + NEO_KHZ800);

//define sound
int count = -1;
int thisNote = 0;

void setup(){
  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(ledMode, OUTPUT);
  pinMode(ledOnboard, OUTPUT);
  pinMode(audioOut, OUTPUT);
  pinMode(sensorInput, INPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(57600);
}

void loop(){

  /* update buttons and mode LEDs and Inputs*/
  updateButtons();
  updateModeLeds();
  updateInputs();

  switch(currentMode){

  case 0: //--- HUMAN CIRCUIT MODE ---
    digitalWrite(ledOnboard, LOW);
    currentVal = analogRead(humanCircuitIn);
    //TODO: map currentVal to 0-1000 or 0-100 or something even

      if(currentVal > 500){
      colorWipe(255, 60, 0, currentVal);
      tone(audioOut, random(100, 1000));
      delay(100);
    }

    else{
      colorWipe(0, 0, 0, currentVal);
      noTone(audioOut);
    }

    //Serial.print("HUMAN currentVal:\t");
    //Serial.println(currentVal);

    break; 

  case 1: //--- REGULAR GADGIT MODE ---
    digitalWrite(ledOnboard, HIGH);
    currentVal = analogRead(gadgitCircuitIn);
    //TODO: map currentVal to 0-1000 or 0-100 or something even

      if(currentVal > 500 || play){
      switch(count){
      case 0:
        noTone(audioOut);
        colorWipe(0, 0, 0, max(currentVal, 1000));
        break;
      case 1:
        windFish();
        colorWipe(0, 255, 0, max(currentVal, 1000));
        break;
      case 2:
        songOfStorms();
        colorWipe(0, 0, 255, max(currentVal, 1000));
        break;
      case 3:
        mario();
        setRainbowToVal(20);
        break;
      }
    }

    else{
      thisNote = 0;
      colorWipe(0, 0, 0, currentVal);
      noTone(audioOut);
    }

    //Serial.print("GADGIT currentVal:\t");
    //Serial.println(currentVal);

    break;

  }//end of switch

}

void updateButtons(){
  /* check both buttons, set the global currentMode to
   * whichever button has last been pressed   */

  int currModeBut = digitalRead(buttonMode); 
  if(currModeBut) {
    currentMode = 0;
    count = -1;
  }

  int currRangeBut = digitalRead(buttonRange); 
  if(currRangeBut) {
    currentMode = 1;
    count = (count + 1) % 4;
    thisNote = 0;
    delay(1000);
  }
}

void updateModeLeds(){
  /* check current mode and turn on correct modeLED */
  if(currentMode)  digitalWrite(ledMode, HIGH);
  else digitalWrite(ledMode, LOW);
}

void updateInputs(){
  sensorState = digitalRead(sensorInput);
  if(sensorState) play = 1;
  else play = 0;
}





















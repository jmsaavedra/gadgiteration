#include "Adafruit_NeoPixel.h"
#include "pitches.h"

/*------------------------DEFINITION------------------------*/
//define all pins
#define buttonMode   2
#define buttonRange  7
#define ledStrip     6
#define ledMode      7
#define audioOut     8
#define ledOnboard   13
#define gadgitCircuitIn A0
#define humanCircuitIn  A1
#define sensorInput    A2

//modes could be 0 - 8
uint8_t currentMode = 0; 

//current sensor value, regardless of human or not
int currentVal = 0; 
int sensorState = 0;
int play = 0;

//define sound
int thisNote = 0;
int randomNumber = 0;

//setup neopixel strip
#define numStripLEDs 20//LED numbers
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numStripLEDs, ledStrip, NEO_GRB + NEO_KHZ800);

/*------------------------SETUP------------------------*/
void setup(){

  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(ledMode, OUTPUT);
  pinMode(ledOnboard, OUTPUT);
  pinMode(audioOut, OUTPUT);
  pinMode(sensorInput, INPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

/*------------------------LOOP------------------------*/
void loop(){

  /* update buttons, mode LEDs and Inputs*/
  updateButtons();
  updateModeLeds();
  updateInputs();

  switch(currentMode){

  case 0: //--- HUMAN CIRCUIT MODE ---
    digitalWrite(ledOnboard, LOW);
    currentVal = analogRead(humanCircuitIn);

    if(currentVal > 500){
      colorWipe(255, 60, 0, currentVal);
      tone(audioOut, random(100, 1000));
      delay(100);
    }

    else{
      colorWipe(0, 0, 0, currentVal);
      noTone(audioOut);
    }

    break; 

  case 1: //--- REGULAR GADGIT MODE ---
    digitalWrite(ledOnboard, HIGH);
    currentVal = analogRead(gadgitCircuitIn);

    if(currentVal > 500 || play){
      switch(randomNumber){
      case 0:
        windFish();
        colorWipe(0, 255, 0, max(currentVal, 1000));
        break;
      case 1:
        songOfStorms();
        colorWipe(0, 0, 255, max(currentVal, 1000));
        break;
      case 2:
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

    break;
  }

}

/*------------------------FUNCTION------------------------*/
void updateButtons(){
  int currModeBut = digitalRead(buttonMode); 
  if(currModeBut) {
    currentMode = 0;
  }
  else {
    currentMode = 1;
  }
}

void updateModeLeds(){
  if(currentMode)  digitalWrite(ledMode, HIGH);
  else digitalWrite(ledMode, LOW);
}

void updateInputs(){
  sensorState = digitalRead(sensorInput);
  if(sensorState) play = 1;
  else play = 0;
}



/*
 Plays a pitch that changes based on a changing analog input
 
 based on code by
 by Tom Igoe 
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone3 
 */

#include "pitches.h"

int analogSensor_1 = A0;
int analogNote_1 = 0;

int analogSampleSize = 10;

int speakerPin = 8;

byte led[] = {
  3,5,6,12,11,10};
int numLeds = 6;
boolean speakerOn = false;

int lowThresh = 50;
int highThresh = 1020;

const int notes[]={
  NOTE_C1,NOTE_CS1,NOTE_D1,NOTE_DS1,NOTE_E1,NOTE_F1,NOTE_FS1,NOTE_G1,NOTE_GS1,NOTE_A1,NOTE_AS1,NOTE_B1,NOTE_C2,NOTE_CS2,NOTE_D2,NOTE_DS2,NOTE_E2,NOTE_F2,NOTE_FS2,NOTE_G2,NOTE_GS2,NOTE_A2,NOTE_AS2,NOTE_B2,NOTE_C3,NOTE_CS3,NOTE_D3,NOTE_DS3,NOTE_E3,NOTE_F3,NOTE_FS3,NOTE_G3,NOTE_GS3,NOTE_A3,NOTE_AS3,NOTE_B3,NOTE_C4,NOTE_CS4,NOTE_D4,NOTE_DS4,NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_A4,NOTE_AS4,NOTE_B4,NOTE_C5,NOTE_CS5,NOTE_D5,NOTE_DS5,NOTE_E5,NOTE_F5,NOTE_FS5,NOTE_G5,NOTE_GS5,NOTE_A5,NOTE_AS5,NOTE_B5,NOTE_C6,NOTE_CS6,NOTE_D6,NOTE_DS6,NOTE_E6,NOTE_F6,NOTE_FS6,NOTE_G6,NOTE_GS6,NOTE_A6,NOTE_AS6,NOTE_B6,NOTE_C7,NOTE_CS7,NOTE_D7,NOTE_DS7,NOTE_E7,NOTE_F7,NOTE_FS7,NOTE_G7,NOTE_GS7,NOTE_A7,NOTE_AS7,NOTE_B7,NOTE_C8,NOTE_CS8};

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
  ledSetup();
}

void loop() {

  //---- ANALOG SENSOR 1
  int analogVal_1;
  for(int i=0; i< analogSampleSize; i++){
    analogVal_1 += analogRead(analogSensor_1);
    delay(5);
  }
  analogVal_1 = analogVal_1/analogSampleSize;
  analogNote_1 = map(analogVal_1, lowThresh, highThresh, 0, 73);

  //  Serial.print("analogVal: ");
  //  Serial.println(analogVal_1);

  int ledDisplay = map(analogNote_1, 0, 50, -1, 6);

  Serial.print("ledDisplay: ");
  Serial.println(ledDisplay);  

  for(int i=0; i<numLeds; i++){
    digitalWrite(led[i], LOW);
  }

  for(int i=-1; i<=ledDisplay; i++){
    digitalWrite(led[i], HIGH); 
  }
  delay(10);

  for(int i=6; i>ledDisplay; i--){
    digitalWrite(led[i], LOW); 
  }

  // if the sensor is pressed hard enough:
  if (analogVal_1 > lowThresh) {
    // play the note corresponding to this sensor:
    tone(speakerPin, notes[analogNote_1], 100);
    if (analogVal_1 > highThresh) {
      tone(speakerPin, notes[random(72)], random(50,250));
    }
  } 


  else {
    noTone(speakerPin); 
  }
}

void ledSetup(){

  int dTime = 100;

  for (int i=0; i<numLeds; i++){
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }

  for (int i=0; i<numLeds; i++){
    digitalWrite(led[i], HIGH);
    delay(dTime);
  }
  //delay(dTime);
  for (int i=numLeds-1; i>=0; i--){
    digitalWrite(led[i], LOW);
    delay(dTime);
  }
}










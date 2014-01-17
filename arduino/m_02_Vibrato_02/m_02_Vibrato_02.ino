/*  Example playing a sinewave with vibrato,
 *  using Mozzi sonification library.
 *
 *  Demonstrates simple FM using phase modulation.
 *
 *  Circuit: Audio output on digital pin 9 (on a Uno or similar), or 
 *  check the README or http://sensorium.github.com/Mozzi/
 *
 *  Mozzi help/discussion/announcements:
 *  https://groups.google.com/forum/#!forum/mozzi-users
 *
 *  Tim Barrass 2012.
 *  This example code is in the public domain.
 */

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/cos2048_int8.h> // table for Oscils to play
#include <mozzi_midi.h> // for mtof
#include <mozzi_analog.h>
#include <EventDelay.h>

#define CONTROL_RATE 64 // powers of 2 please

EventDelay <CONTROL_RATE>  ledDelay;

#define ANALOG_IN A0
#define RANGE_SETTER A4
#define MODE_SETTER A5
#define LED_PIN 13

Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCos(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aVibrato(COS2048_DATA);

int mode = 0; //0=playing audio mode A, 1=playing audio mode B, 2=setting high/low

const long intensity = 300;

void setup(){
  startMozzi(CONTROL_RATE);
  aCos.setFreq(mtof(84.f));
  aVibrato.setFreq(15.f);
  setupFastAnalogRead();
  pinMode(LED_PIN, OUTPUT);
  ledDelay.set(1000);
  Serial.begin(9600);
}

void loop(){
  //if (mode < 2) 
  audioHook();
}

void updateControl(){

  unsigned char vibFreq = (unsigned char) (analogRead(ANALOG_IN)>>2);
  unsigned char rangeButton = (unsigned char) (analogRead(RANGE_SETTER));
  unsigned char modeButton = (unsigned char) (analogRead(MODE_SETTER));
  
  //Serial.println( setMode );
  Serial.println( rangeButton );

  if(rangeButton > 150){
    mode = 2;
    ledDelay.start(); 
  }

  if(mode == 0) {
    digitalWrite(LED_PIN, LOW);
    //vibFreq = map(vibFreq, 30, 285, 0, 255);
    aVibrato.setFreq((float)(vibFreq/40 + 3.f));
    aCos.setFreq((float)(vibFreq*5+100.f));
  }

  else if(mode == 1){
    digitalWrite(LED_PIN, LOW);
    //another audio effect 
  }

  else if(mode == 2){ //set range mode
    //setting the high and low
    aVibrato.setFreq((float)5.f);
    aCos.setFreq((float)5.f);
    
    flashLED();
    Serial.print("range set val: ");
    Serial.println( analogRead(ANALOG_IN) );
    if(ledDelay.ready()){
      mode = 0;
    }
  }
}

int updateAudio(){
  long vibrato = intensity * aVibrato.next();
  return (int)aCos.phMod(vibrato);
}

void flashLED(){

  digitalWrite(13, HIGH);
  //delay(100);
  //digitalWrite(13, LOW);
  //delay(100); 
}


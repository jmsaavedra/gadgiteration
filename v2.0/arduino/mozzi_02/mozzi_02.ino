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

#define CONTROL_RATE 64 // powers of 2 please

#define ANALOG_IN A0

#define RANGE_SETTER D5

#define MODE_SETTER D7

Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCos(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aVibrato(COS2048_DATA);

 const long intensity = 300;

void setup(){
  startMozzi(CONTROL_RATE);
  aCos.setFreq(mtof(84.f));
  aVibrato.setFreq(15.f);
  setupFastAnalogRead();
}

void loop(){
  audioHook();
}

void updateControl(){
  
  unsigned char vibFreq = (unsigned char) (analogRead(ANALOG_IN)>>2);
  //vibFreq = map(vibFreq, 30, 285, 0, 255);
  aVibrato.setFreq((float)(vibFreq/40 + 3.f));
  aCos.setFreq((float)(vibFreq*5+100.f));
}

int updateAudio(){
    long vibrato = intensity * aVibrato.next();
    return (int)aCos.phMod(vibrato);
}

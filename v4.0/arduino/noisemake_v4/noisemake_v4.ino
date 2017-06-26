#include "Adafruit_NeoPixel.h"
#include "pitches.h"

/* still in progress */

//define all pins
#define buttonMode      2
#define buttonRange     7
#define ledStrip        6
#define boardPixel      5
#define ledMode         7
#define audioOut        8
#define gadgitCircuitIn A0
#define humanCircuitIn  A1
#define sensorInput     A2

//modes could be 0 - 8
uint8_t currentMode = 0;

//current sensor value, regardless of human or not
int currentVal = 0;
int sensorState = 0;
int play = 0;

//setup neopixels
#define numStripLEDs 13 //how many LEDs long
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numStripLEDs, ledStrip, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel onboard = Adafruit_NeoPixel(1, boardPixel, NEO_GRB + NEO_KHZ800);

//define sound
int thisNote = 0;
int randomNumber = 0 ;

void setup() {
  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(ledMode, OUTPUT);
  pinMode(audioOut, OUTPUT);
  pinMode(sensorInput, INPUT);

  updateModeLed();

  onboard.begin();
  onboard.show();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(57600);

}

void loop() {

  /* update buttons and mode LEDs and Inputs*/
  updateButtons();
  updateInputs();

  switch (currentMode) {

    case 0: //--- HUMAN CIRCUIT MODE ---
      currentVal = analogRead(humanCircuitIn);
      Serial.print("human circuit currentVal: ");
      Serial.println(currentVal);
      //TODO: map currentVal to 0-1000 or 0-100 or something even

      if (currentVal > 5) {
        colorWipe(255, 60, 0, currentVal);
        tone(audioOut, random(100, 100 + currentVal));
        delay(100);
      }

      else {
        colorWipe(0, 0, 0, currentVal);
        noTone(audioOut);
      }
      break;

    case 1: //--- REGULAR GADGIT MODE ---

      currentVal = analogRead(gadgitCircuitIn);
      Serial.print("alligator clips currentVal: ");
      Serial.println(currentVal);
      //TODO: map currentVal to 0-1000 or 0-100 or something even

      if (currentVal > 500 || play) {
        //if(currentVal > 500){
        switch (randomNumber) {
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
      } else {
        thisNote = 0;
        colorWipe(0, 0, 0, currentVal);
        noTone(audioOut);
      }
      break;

    case 2:
      rainbowCycleStrip(1); //NOTE: This code is blocking!!
      onboard.setPixelColor(0, onboard.Color(random(100), random(100), random(100))); // Moderately bright random color.
      onboard.show();
      break;

    default:
      Serial.print("unrecognized mode: ");
      Serial.print(currentMode);
      break;
  }//end of switch
}


void updateInputs() {
  sensorState = digitalRead(sensorInput);
  if (sensorState) play = 1;
  else play = 0;
}

//------------------------------neopixels------------------------

// Fill the dots one after the other with a color
void colorWipe(uint32_t r, uint32_t g, uint32_t b, int val) {
  //assumes val is 0 - 1000, and that we have 10 LEDs
  //TODO: map this properly

  int numLedsToLight = int(val / 50);
  for (uint16_t i = 0; i < numLedsToLight; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }

  for (uint16_t i = numLedsToLight; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }

  strip.show();
  // delay(10);
}

void setRainbowToVal(uint8_t wait) {
  static uint16_t j = 0;

  Serial.println(j);
  if (j >= 256 - 1) j = 0;

  int temp = j + 3;
  for (; j < temp; j++)
    for (uint16_t i = 0; i < strip.numPixels(); i++)
      strip.setPixelColor(i, Wheel((i + j) & 255));

  strip.show();
  delay(wait);
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbowCycleStrip(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


//------------------------------songs------------------------

//define notes
//windFish
int melody1[] = {
  NOTE_D5, NOTE_E5, NOTE_F5,
  NOTE_D5, NOTE_E5, NOTE_F5,
  NOTE_E5, NOTE_D5, NOTE_A4,
  NOTE_C5, NOTE_D5, 0
};
int noteDurations1[] = {
  200, 200, 800,
  200, 200, 800,
  200, 200, 200,
  600, 600, 600
};

//songOfStorms
int melody2[] = {
  NOTE_D4, NOTE_F4, NOTE_D5,
  NOTE_D4, NOTE_F4, NOTE_D5,
  NOTE_E5, NOTE_F5, NOTE_E5,
  NOTE_F5, NOTE_E5, NOTE_C5, NOTE_A4, 0
};
int noteDurations2[] = {
  200, 200, 600,
  200, 200, 600,
  600, 200, 200,
  200, 200, 200, 600, 600
};

//overWorld
int melody3[] = {
  NOTE_A4, NOTE_E4, NOTE_A4,
  NOTE_A4, NOTE_B4, NOTE_C5,
  NOTE_D5, NOTE_E5, 0
};
int noteDurations3[] = {
  300, 600, 200,
  200, 200, 200,
  200, 600, 600
};

//mario
int melody4[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
  NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_C4,
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations4[] = {
  8, 4, 4, 8, 4, 2, 2,
  3, 3, 3, 4, 4, 8, 4, 8, 8, 8, 4, 8, 4, 3, 8, 8, 3,
  3, 3, 3, 4, 4, 8, 4, 8, 8, 8, 4, 8, 4, 3, 8, 8, 2,
  8, 8, 8, 4, 4, 8, 8, 4, 8, 8, 3, 8, 8, 8, 4, 4, 4, 8, 2,
  8, 8, 8, 4, 4, 8, 8, 4, 8, 8, 3, 3, 3, 1,
  8, 4, 4, 8, 4, 8, 4, 8, 2, 8, 4, 4, 8, 4, 1,
  8, 4, 4, 8, 4, 8, 4, 8, 2
};

//play windFish
void windFish() {
  int noteDuration = noteDurations1[thisNote];
  tone(audioOut, melody1[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 12;
}

//play songOfStorms
void songOfStorms() {
  int noteDuration = noteDurations2[thisNote];
  tone(audioOut, melody2[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 14;
}

//play overWorld
void overWorld() {
  int noteDuration = noteDurations3[thisNote];
  tone(audioOut, melody3[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 9;
}

//play mario
void mario() {
  int noteDuration = 1000 / noteDurations4[thisNote];
  tone(audioOut, melody4[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 98;
}


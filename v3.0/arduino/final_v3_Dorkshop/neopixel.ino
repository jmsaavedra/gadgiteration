/*------------------------NEOPIXEL DEFINITION------------------------*/

// Fill the dots one after the other with a color
void colorWipe(uint32_t r, uint32_t g, uint32_t b, int val) {
  //assumes val is 0 - 1000, and that we have 10 LEDs
  //TODO: map this properly

  int numLedsToLight = int(val/50);
  for(uint16_t i = 0; i < numLedsToLight; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }

  for(uint16_t i = numLedsToLight; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }

  strip.show();
  // delay(10);
}

void setRainbowToVal(uint8_t wait){
  static uint16_t j = 0;

  Serial.println(j);
  if(j >= 256 - 1) j = 0;

  int temp = j + 3;
  for(;j < temp; j++)
    for(uint16_t i = 0; i < strip.numPixels(); i++)
      strip.setPixelColor(i, Wheel((i+j) & 255));

  strip.show();
  delay(wait); 
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

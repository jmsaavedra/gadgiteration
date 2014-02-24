
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, int val) {
   //assumes val is 0 - 1000, and that we have 10 LEDs
   //TODO: map this properly
   
  int numLedsToLight = int(val/100);
 
  for(uint16_t i=0; i<numLedsToLight; i++) {
      strip.setPixelColor(i, strip.Color(0,c,0));
  }
  
  for(uint16_t i=numLedsToLight; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
  }
  
  strip.show();
 // delay(10);
}



void setRainbowToVal(int val){
 //assumes val is 0 - 1000 
  uint16_t i, j;
  int numLedsToLight = val/1000;

//  for(j=0; j<256; j++) {
    for(i=0; i<val; i++) {
      strip.setPixelColor(i, Wheel((i+125) & 255));
    }
    strip.show();
    delay(10);
//  }  
}



void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
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

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define ONBOARDPIN  5 // on-board Neo
#define STRIPPIN    6 // external strip pin

Adafruit_NeoPixel onboard = Adafruit_NeoPixel(1 /*1 pixel*/, ONBOARDPIN, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(13 /*13 pixels*/, STRIPPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  onboard.begin(); // This initializes the NeoPixel library.
  strip.begin();
}

void loop() {

  rainbowCycleStrip(5);

  /*** setPixelColor(pixelNumber, pixel.Color(R, G, B))***/
  /*** pixels.Color takes RGB values, from 0,0,0 up to 255,255,255 */
  onboard.setPixelColor(0, onboard.Color(random(100), random(100), random(100))); // Moderately bright random color.
  onboard.show();
    
//  for(int i=0;i<100;i++){
//    onboard.setPixelColor(0, onboard.Color(i, 100-i, i)); // Moderately bright green color.
//    onboard.show(); // This sends the updated pixel color to the hardware.
//    delay(10); // Delay for a period of time (in milliseconds).
//  }
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



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

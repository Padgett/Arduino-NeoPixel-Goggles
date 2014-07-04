// NeoPixel Goggles
// Modified by Joshua Padgett July, 2014 to allow for variable strip length and array of colors
// Original code: Adafruit's Kaleidoscope Eyes https://learn.adafruit.com/kaleidoscope-eyes-neopixel-led-goggles-trinket-gemma/software

// Requires Adafruit's Neopixel Library
#include <Adafruit_NeoPixel.h>

#define PIN 0
#define STRIPLEN 32

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(STRIPLEN, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
int      colorswitch = 0, // First color selection
         colorcount = 2; // 3 colors, array zero based
         
uint32_t color[]  = {0xFF0000, 0xFFFFFF, 0x0000FF}; // R->W->B for Independence Day, Start red
uint32_t prevTime;

void setup() {
  pixels.begin();
  pixels.setBrightness(42); // 1/6 brightness
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  uint32_t t;

  switch(mode) {

   case 0: // Random sparks - just one LED on at a time!
    i = random(STRIPLEN);
    pixels.setPixelColor(i, color[random(0,colorcount+1)]); // Random max is -1
    pixels.show();
    delay(10);
    pixels.setPixelColor(i, 0);
    break;
 
   case 1: // Spinny wheels (8 LEDs on at a time)
    for(i=0; i<STRIPLEN; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < 2) c = color[colorswitch]; // 4 pixels on...
      pixels.setPixelColor(i, c); // First eye
      pixels.setPixelColor((STRIPLEN-1)-i, c); // Second eye (flipped)
    }
    pixels.show();
    offset++;
    delay(50);
    break;
  }

  t = millis();
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    mode++;                        // Next mode
    if(mode > 1) {                 // End of modes?
      mode = 0;                    // Start modes over
      colorswitch++;               // Next color
      if(colorswitch > colorcount) colorswitch = 0; // Reset to first
    }
    for(i=0; i<STRIPLEN; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define num_pixels 2
#define NUM_LEDS 16*num_pixels

#define PIN 6
#define WINDOW 20
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW);

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}


void colorAnim(uint8_t wait){
  /*
   * takes a number 0-255 and loops through all the pixels to set them to that color
   */
  uint32_t color = Wheel(random(0, 255));
  //for(int i=0; i<NUM_LEDS; i++) { //loop through all the pixels
  for(int i=16; i >= 0; i--) {
      strip.setPixelColor(i, color);
      strip.setPixelColor(i+15, color);
      strip.show();
      
      delay(wait);
    }
}


uint32_t Wheel(byte WheelPos) {
/*
 * Wheel transforms a number 0 to 255 to a color
 * Input a value 0 to 255 to get a color value.
 * The colours are a transition r - g - b - back to r.
 */
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


void loop() {
  
  colorAnim(10);
  
}

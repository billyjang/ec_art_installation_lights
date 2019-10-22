#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define num_pixels 19
#define NUM_LEDS 12*num_pixels

#define PIN 2
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
  //uint32_t color = Wheel(random(0, 255));
  for(int i=0; i<NUM_LEDS; i++) { //loop through all the pixels
      strip.setPixelColor(i, 50, 0, 50);
     
      strip.show();
      
      delay(wait);
    }
}

void loop() {
  
  colorAnim(10);
  
}

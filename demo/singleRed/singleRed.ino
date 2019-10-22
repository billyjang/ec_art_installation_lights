#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define num_pixels 2
#define NUM_LEDS 16*num_pixels

#define PIN 6
#define WINDOW 20
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW);

uint32_t colors[] = {
  strip.Color(100,0,0),
  strip.Color(120,20,0),
  strip.Color(100,100,0),
  strip.Color(0,100,0),
  strip.Color(0,100,50),
  strip.Color(0,50,100),
  strip.Color(0,0,100),
  strip.Color(100,0,100),
};

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void colorAnim(uint8_t wait) {
  wipe(100);
  traveler(100);
}

void traveler(uint8_t wait) {
  uint32_t color = strip.Color(0,0,0,100);
  uint16_t startx = 2;
  uint16_t starty = 3;
  uint16_t nextx = 0;
  uint16_t nexty = 0;
  for(uint16_t i = 0; i < 8; i++) {
    uint16_t j = i - 1;
    nextx = (startx - i) % 16;
    nexty = (starty + i) % 16;
    uint16_t oldx = (startx - j) % 16;
    uint16_t oldy = (starty + j) % 16;
    strip.setPixelColor(oldx, colors[j]);
    strip.setPixelColor(oldy, colors[j]);
    strip.setPixelColor(oldx + 16, colors[j]);
    strip.setPixelColor(oldy + 16, colors[j]);
    strip.setPixelColor(nextx, color);
    strip.setPixelColor(nexty, color);
    strip.setPixelColor(nextx + 16, color);
    strip.setPixelColor(nexty + 16, color);
    delay(wait);
    strip.show();
  }
  
}

int32_t returnColor(uint8_t index) {
  return colors[index];
}
void wipe(uint8_t wait) {
  uint32_t color = strip.Color(50,0,0);
  uint16_t startx = 2;
  uint16_t starty = 3;
  for(uint16_t i = 0; i < 8; i++) {
    uint32_t color = returnColor(i);
    
    strip.setPixelColor((startx - i) % 16, color);
    strip.setPixelColor((starty + i) % 16, color);
    strip.setPixelColor((startx - i) % 16 + 16, color);
    strip.setPixelColor((starty + i) % 16 + 16, color);
    delay(wait);
    strip.show();
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

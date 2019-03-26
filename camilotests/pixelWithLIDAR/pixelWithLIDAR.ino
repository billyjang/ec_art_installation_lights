#include "Adafruit_VL53L0X.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 2
#define num_neoPixels 1 // change depending on num of neoPixels
#define num_leds num_neoPixels*12

Adafruit_VL53L0X lox = Adafruit_VL53L0X(); //our precious LIDAR sensor


Adafruit_NeoPixel strip = Adafruit_NeoPixel(num_leds, PIN, NEO_GRBW + NEO_KHZ800);


void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void distanceToColor(uint8_t wait, float distance){
  /*
   * takes a number 0-255 and loops through all the pixels to set them to that color
   */
   
  for(int i=0; i<num_leds; i++) { //loop through all the pixels
      strip.setPixelColor(i, Wheel(distance));
    }
    strip.show();
    delay(wait);
}

float look(){
   /*
   * Code below reads the distance from the LIDAR (mm)
   * and converts it to color (0 - 255)
   */

   VL53L0X_RangingMeasurementData_t measure;
    
    Serial.print("Reading a measurement... ");
    // read the input

    int distance = 0;

    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
        distance = measure.RangeMilliMeter;
    } else {
        distance = 0;
    }

    Serial.print("Distance (mm): "); Serial.println(distance);
    
    // Convert the analog reading (which goes from 0 - 500 mm) to a color (0 - 255):
    float value = distance * (255.0 / 500);
    
    return value;  
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

  distanceToColor(20, look());
  delay(100);
  
}

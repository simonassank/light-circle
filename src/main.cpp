#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 20

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS);
}

int hue = 0;

void loop() { 
  int ledIndex = 0;
  int output = analogRead(A8);
  while (ledIndex < NUM_LEDS) {
    // leds[ledIndex].setHue(hue/0);
    leds[ledIndex].setHSV(output/2, 255, 100);
    hue++;
    ledIndex++;
  }
  FastLED.show();
  // Serial.println(output);
  // delay(8);
}

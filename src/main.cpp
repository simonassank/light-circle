#include <Arduino.h>
#include <FastLED.h>
#include <magic.hpp>

#define NUM_LEDS 20

CRGB leds[NUM_LEDS];

Magic magic = Magic(A8, 20000);

void setup() {
    digitalWrite(LED_BUILTIN, HIGH);
    FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS);
}

void loop() {
    magic.loop();
    
    int ledIndex = 0;
    int hue = (magic.peakFrequency / 10000) * 360;
    while (ledIndex < NUM_LEDS) {
        leds[ledIndex].setHSV(hue, 255, 100);
        ledIndex++;
    }

    FastLED.show();
}

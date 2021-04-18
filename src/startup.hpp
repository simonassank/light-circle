#include <FastLED.h>

const int startupTime = 5000;

void showStartupAnimation(CRGB * leds, int ledCount) {
    FastLED.clear(true); 
    for (int loop = 0; loop < 300; loop++) {
        for (int i = 1; i <= ledCount; i++) {
            int power = (100 * abs(sin(millis() / 1000.0))) + 50;
            int hue = 360 * sin(millis() / 1000.0 + (i / 20.0));
            leds[i-1].setHSV(hue, 200, power);
        }
        FastLED.show(); 
        delay(16);
    }
    FastLED.clear(true); 
};
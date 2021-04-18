#include <Arduino.h>
#include <FastLED.h>
#include <magic.hpp>
#include <startup.hpp>
#include <Audio.h>

#define NUM_LEDS_PER_STRIP 9
#define NUM_STRIPS 1
#define NUM_LEDS   NUM_LEDS_PER_STRIP  
#define DATA_PIN 10

CRGB leds[NUM_LEDS];

Magic magic = Magic(A1);

void setup() {
    digitalWrite(LED_BUILTIN, HIGH);
    
    AudioMemory(8);
    Serial.begin(9600);
    Serial.println("Waiting for serial!");
    // while (!Serial);
    
    FastLED.addLeds<NUM_STRIPS, WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);

    showStartupAnimation(leds, NUM_LEDS);
}

void loop() {
    // Serial.println("Loop");
    // long startAt = millis();
    magic.loop();
    FastLED.clear(0);
    int hue = 360 * (magic.pitch / 1500);
    int value = (200 * magic.power) + 50;
    
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setHSV(hue, 255, value);
    }

    FastLED.show();

    // Serial.println("End: ");
    // Serial.println(millis() - startAt);
    // delay(100);
}

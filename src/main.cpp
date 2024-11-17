#include <Arduino.h>
#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  FastLED.showColor(CRGB::Blue);
}
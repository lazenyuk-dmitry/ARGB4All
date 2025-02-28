#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 60
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

struct Parser {
  unsigned int key;
	String value;
};

Parser parseSerialString(String string) {
  int position = string.indexOf(':');
  String key = string.substring(0, position);
  String value = string.substring(position + 1, string.length());
  return {key.toInt(), value};
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(0);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  FastLED.showColor(CRGB::Blue);

  if (Serial.available() > 0) {
    String str = Serial.readStringUntil(';');
    Parser data = parseSerialString(str);
    Serial.println(str);
    Serial.println(data.key);
    Serial.println(data.value);
  }
}
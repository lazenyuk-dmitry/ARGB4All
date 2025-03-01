#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "parser.h"
#include "helpers.h"

CRGB leds[NUM_LEDS];
CRGB color = CRGB::Blue;
uint8_t brightness = 100;

void updateColor(String strValue);
void update(Parser data);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(0);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  FastLED.showColor(color);
  FastLED.setBrightness(brightness);

  if (Serial.available() > 0) {
    String str = Serial.readStringUntil(';');
    Parser data = parseSerialString(str);
    // Serial.print(String(data.key) + ':' + data.value + ';');
    update(data);
  }
}

void update(Parser data) {
  switch (data.key) {
    case COLOR_KEY:
      updateColor(data.value);
      break;

    default:
      break;
  }
}

void updateColor(String strValue) {
  String values[3];
  parseSerialValue(strValue, values);
  color = CRGB(values[0].toInt(), values[2].toInt(), values[3].toInt());
}

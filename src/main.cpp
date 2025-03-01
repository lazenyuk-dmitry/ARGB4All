#include <Arduino.h>
#include <FastLED.h>
#include "config.h"

CRGB leds[NUM_LEDS];
CRGB color = CRGB::Blue;
uint8_t brightness = 100;

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

void parseSerialValue(String strValue, String *buf) {
  char terminator = ',';
  unsigned int bufIndex = 0;
  int position = 0;

  while (position < strValue.length()) {
    int positionNext = strValue.indexOf(terminator, position + 1);

    if (positionNext == -1) {
      positionNext = strValue.length();
    }

    String subStr = strValue.substring(position > 0 ? position + 1 : 0, positionNext);
    buf[bufIndex] = subStr;

    position = positionNext;
    bufIndex++;
  }
}

void updateColor(String strValue) {
  String values[3];
  parseSerialValue(strValue, values);
  color = CRGB(values[0].toInt(), values[2].toInt(), values[3].toInt());
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

void serialWrite(String str) {
  Serial.print(str + ';');
}

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
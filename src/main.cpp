#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "parser.h"
#include "helpers.h"

CRGB leds[NUM_LEDS];
CRGB color = CRGB::Blue;
uint8_t brightness = 255;
bool connected = false;

void updateColor(String strValue);
void updateBrigthtness(String strValue);
void update(Parser data);
void sendConnected();

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(0);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  FastLED.showColor(color);
  FastLED.setBrightness(brightness);

  if (Serial) {
    if (!connected) {
      sendConnected();
    }
    connected = true;
  } else if (!Serial) {
    connected = false;
  }

  if (Serial.available() > 0) {
    String str = Serial.readStringUntil(';');
    Parser data = parseSerialString(str);
    update(data);
  }
}

void update(Parser data) {
  switch (data.key) {
    case COLOR_KEY:
      updateColor(data.value);
      break;

    case BRIGHTNESS_KEY:
      updateBrigthtness(data.value);
      break;

    default:
      break;
  }
}

void sendConnected() {
  String str = "";
  str += String(COLOR_KEY) + ":" + String(color[0]) + "," + String(color[1]) + "," + String(color[2]);
  str += "+" + String(BRIGHTNESS_KEY) + ":" + String(convert255To100(brightness));
  serialWrite(str);
}

void updateColor(String strValue) {
  String values[3];
  parseSerialValue(strValue, values);
  color = CRGB(values[0].toInt(), values[1].toInt(), values[2].toInt());
}

void updateBrigthtness(String strValue) {
  brightness = convert1000To255(strValue.toInt());
}

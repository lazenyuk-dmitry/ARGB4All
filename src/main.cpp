#include <Arduino.h>
#include <EEPROM.h>
#include <FastLED.h>
#include "config.h"
#include "constants.h"
#include "parser.h"
#include "helpers.h"

CRGB leds[NUM_LEDS];
CRGB color = CRGB::Blue;
uint8_t brightness = 255;
bool connected = false;

void updateColor(String strValue);
void updateBrigthtness(String strValue);
void update(Parser data);
void sendParams();
void eepromUpdate();
void restoreFromEeprom();
void resetToDefaults();

void setup() {
  byte initFlag;
  EEPROM.get(0, initFlag);

  if (initFlag != EEPROM_INIT_KEY) {
    EEPROM.put(0, EEPROM_INIT_KEY);
    eepromUpdate();
  } else {
    restoreFromEeprom();
  }

  Serial.begin(9600);
  Serial.setTimeout(0);
  pinMode(POWER_PIN, INPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  if (digitalRead(POWER_PIN) == LOW) {
    FastLED.clear();
    FastLED.show();
    return;
  }

  FastLED.showColor(color);
  FastLED.setBrightness(brightness);

  if (Serial) {
    if (!connected) {
      sendParams();
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
  if (data.key == COLOR_KEY) {
    updateColor(data.value);
  }
  else if (data.key == BRIGHTNESS_KEY) {
    updateBrigthtness(data.value);
  }
  else if (data.key == SAVE_KEY) {
    eepromUpdate();
  }
  else if (data.key == RESET_KEY) {
    resetToDefaults();
  }
}

void sendParams() {
  String colors[] = { String(color[0]), String(color[1]), String(color[2]) };
  String serialStr = parseArrayToSerialValue(colors, sizeof(colors) / sizeof(colors[0]));
  serialWrite(COLOR_KEY, serialStr);
  serialWrite(BRIGHTNESS_KEY, String(convert255To100(brightness)));
}

void updateColor(String strValue) {
  String values[3];
  parseSerialValue(strValue, values);
  color = CRGB(values[0].toInt(), values[1].toInt(), values[2].toInt());
}

void updateBrigthtness(String strValue) {
  brightness = convert1000To255(strValue.toInt());
}

void eepromUpdate() {
  EEPROM.update(EEPROM_R, color[0]);
  EEPROM.update(EEPROM_G, color[1]);
  EEPROM.update(EEPROM_B, color[2]);
  EEPROM.update(EEPROM_BRIGTHNESS, brightness);
}

void restoreFromEeprom() {
  color[0] = EEPROM.read(EEPROM_R);
  color[1] = EEPROM.read(EEPROM_G);
  color[2] = EEPROM.read(EEPROM_B);
  EEPROM.get(EEPROM_BRIGTHNESS, brightness);
}

void resetToDefaults() {
  color = DEFAULT_COLOR;
  brightness = DEFAULT_BRIGTHNESS;
  eepromUpdate();
  sendParams();
}
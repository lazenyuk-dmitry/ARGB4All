#include <Arduino.h>
#include "helpers.h"

void serialWrite(String str) {
  Serial.print(str + ';');
}

int convert255To100(uint8_t value) {
  return round((double (value) / 255.0) * 100.0);
}
int convert1000To255(uint8_t value) {
  return round((double (value) / 100.0) * 255.0);
}
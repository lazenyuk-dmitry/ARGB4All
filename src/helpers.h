#include <Arduino.h>

void serialWrite(String key, String value = "");

int convert255To100(uint8_t value);
int convert1000To255(uint8_t value);
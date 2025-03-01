#include <Arduino.h>
#include "helpers.h"

void serialWrite(String str) {
  Serial.print(str + ';');
}
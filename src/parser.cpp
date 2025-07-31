#include <Arduino.h>
#include "parser.h"


Parser parseSerialString(String string) {
  int position = string.indexOf(':');
  String key = string.substring(0, position);
  String value = string.substring(position + 1, string.length());
  return {key, value};
}

void parseSerialValue(String strValue, String *buf) {
  char terminator = ',';
  unsigned int bufIndex = 0;
  unsigned int position = 0;

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
#include <Arduino.h>

struct Parser {
  unsigned int key;
	String value;
};

Parser parseSerialString(String string);

void parseSerialValue(String strValue, String *buf);

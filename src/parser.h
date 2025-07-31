#include <Arduino.h>

struct Parser {
  String key;
	String value;
};

Parser parseSerialString(String string);

void parseSerialValue(String strValue, String *buf);

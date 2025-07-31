#include <Arduino.h>

struct Parser {
  String key;
	String value;
};

Parser parseSerialString(String string);

void parseSerialValue(String strValue, String *buf);

String parseArrayToSerialValue(const String* args, unsigned int argsCount);

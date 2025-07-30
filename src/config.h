#define NUM_LEDS 60
#define POWER_PIN 2
#define DATA_PIN 3

// Defaults
#define DEFAULT_COLOR CRGB::Blue
#define DEFAULT_BRIGTHNESS 255

// COM data keys
#define COLOR_KEY 0
#define BRIGHTNESS_KEY 1
#define SAVE_KEY 100
#define RESET_KEY 101

// EEPROM
#define EEPROM_INIT_KEY 0x42
#define EEPROM_INIT 0
#define EEPROM_R 1
#define EEPROM_G 2
#define EEPROM_B 3
#define EEPROM_BRIGTHNESS 4

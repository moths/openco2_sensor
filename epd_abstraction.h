#ifndef EPD_ABSTRACTION_H
#define EPD_ABSTRACTION_H

#define MQTT
// #define airgradient

#include <stdlib.h>
#include <Preferences.h>
#include <WiFi.h>
#ifdef MQTT
#include <ArduinoMqttClient.h>
#endif


#define NUM_MEASUREMENTS (24*120)
#define VERSION "v6.1"
#define BUTTON GPIO_NUM_0

enum MenuOptions {
  LED,
  DISPLAY_MENU,
  CALIBRATE,
  HISTORY,
  WLAN,
  INFO,
  FUN,
  NUM_OPTIONS
};
enum LEDMenuOptions {
  onBATTERY,
  onUSB,
  COLOR,
  BRIGHTNESS,
  EXIT_LED,
  NUM_LED_OPTIONS
};
enum DisplayMenuOptions {
  MAX_BATTERY,
  INVERT,
  TEMP_UNIT,
  LANGUAGE,
  FONT,
  RESET_DISPLAY,
  EXIT_DISPLAY,
  NUM_DISPLAY_OPTIONS
};
enum FUNMenuOptions {
  RAINBOW,
  SNAKE,
  //TICTACTOE,
  EXIT_FUN,
  NUM_FUN_OPTIONS
};

/* ENGLISH */
const char* EnglishMenuItems[NUM_OPTIONS] = {
  "LED",
  "Settings",
  "Calibrate",
  "History",
  "Wi-Fi",
  "Info",
  "Fun"
};
const char* EnglishLEDmenuItems[NUM_LED_OPTIONS] = {
  "Battery",
  "on USB",
  "Color",
  "Bright",
  "Exit"
};
const char* EnglishOptionsMenuItems[NUM_DISPLAY_OPTIONS] = {
  "Battery",
  "Invert",
  "Unit",
  "English",
  "Font",
  "Reset",
  "Exit"
};
const char* EnglishFUNmenuItems[NUM_FUN_OPTIONS] = {
  "Rainbow",
  "Snake",
  //"TicTacToe",
  "Exit"
};

/* GERMAN */
const char* GermanMenuItems[NUM_OPTIONS] = {
  "LED",
  "Einst.",
  "Kalibrieren",
  "Historie",
  "WLAN",
  "Info",
  "Spass"
};
const char* GermanLEDmenuItems[NUM_LED_OPTIONS] = {
  "Batterie",
  "mit USB",
  "Farbe",
  "Hell",
  "Beenden"
};
const char* GermanOptionsMenuItems[NUM_DISPLAY_OPTIONS] = {
  "Battery",
  "Invert",
  "Einheit",
  "German",
  "Schrift",
  "Reset",
  "Beenden"
};
const char* GermanFUNmenuItems[NUM_FUN_OPTIONS] = {
  "Regenbogen",
  "Snake",
  //"TicTacToe",
  "Beenden"
};

typedef struct {
    uint8_t humidity : 7;      // 7 bits (range 0 to 100)
    uint16_t temperature : 9;  // 9 bits (/10= range 0 to 51.1°C )
} tempHumData;

/* Globals defined in OpenCO2_Sensor.ino */
extern bool USB_ACTIVE, initDone, BatteryMode, comingFromDeepSleep;
extern bool LEDonBattery, LEDonUSB, useSmoothLEDcolor, invertDisplay, useFahrenheit, useWiFi, english, limitMaxBattery;
extern uint8_t ledbrightness, HWSubRev, font, skipMeasurement;
extern float maxBatteryVoltage;
extern bool TEST_MODE;
extern uint16_t sensorStatus;
extern uint64_t serialNumber;
extern uint16_t co2;
extern float temperature, humidity;
extern uint16_t currentIndex;
extern bool overflow;
extern uint16_t co2measurements[NUM_MEASUREMENTS];
extern tempHumData tempHumMeasurements[NUM_MEASUREMENTS / 4];
extern float sumTemp;
extern char mqtt_server[40];
extern char mqtt_port[6];
extern char mqtt_user[34];
#ifdef MQTT
extern MqttClient mqttClient;
#endif
extern Preferences preferences;

/* And in epd_abstraction.ino */
extern uint16_t refreshes;

/* epd_abstraction.ino */
void handleButtonPress();
void displayResetConfirmation();
void displayinfo2();
void changeFont(int font);
void displayWelcome();
void initEpdOnce();
void displayInitTestMode();
void displayInit();
void displayLowBattery();
void displayWriteError(char errorMessage[256]);
void displayWriteMeasuerments(uint16_t co2, float temperature, float humidity);
void displayWriteTestResults(float voltage, uint16_t sensorStatus);
void displayBattery(uint8_t percentage);
void updateDisplay();
void displayImage(const unsigned char* image_buffer);
void displayCalibrationWarning();
void DisplayCalibrationFail();
void DisplayCalibrationResult(int correction);
void displayWiFi(bool useWiFi);
void displayWiFiStrengh();

/* OpenCO2_Sensor.ino */
void setLED(uint16_t co2);
void updateBatteryMode();
float readBatteryVoltage();
void toggleMaxBattery();
uint8_t calcBatteryPercentage(float voltage);
void calibrate();
void factoryReset();
void rainbowMode();
void saveMeasurement(uint16_t co2, float temperature, float humidity);
uint16_t getCO2Measurement(uint16_t index);
uint16_t getTempMeasurement(uint16_t index);
uint8_t getHumMeasurement(uint16_t index);
void toggleWiFi();

#endif /* EPD_ABSTRACTION_H */

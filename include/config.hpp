#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

extern const uint8_t lcdSDA;
extern const uint8_t lcdSCL;
extern const uint8_t servoPin;

extern const float tempThreshold;

extern const uint32_t debounceDelay;
extern const uint32_t debounceDelayReconnectMQTT;
extern const uint32_t delayCompressorTurn;

extern const char *ssid;
extern const char *password;

extern const char* MQTT_BROKER;
extern const uint16_t MQTT_PORT;

#endif // CONFIG_H

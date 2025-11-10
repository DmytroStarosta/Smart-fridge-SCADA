#include <Arduino.h>

#include "../include/config.hpp"
#include "../my.cpp"

const uint8_t servoPin = 13;
const uint8_t lcdSDA = 21;
const uint8_t lcdSCL = 22;

const float tempThreshold = 5.0;

const uint32_t debounceDelay = 2000;
const uint32_t debounceDelayReconnectMQTT = 5000;
const uint32_t delayCompressorTurn = 500;

const char* ssid = my_ssid;
const char* password = my_password;

const char* MQTT_BROKER = my_mqtt_broker;
const uint16_t MQTT_PORT = my_mqtt_port;

#ifndef INITPINS_H
#define INITPINS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP32Servo.h>

extern LiquidCrystal_I2C lcd;
extern DHT dht;
extern Servo compressorServo;

void initPins();

#endif // INITPINS_H

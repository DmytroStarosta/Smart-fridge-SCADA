#include <Arduino.h>
#include <PubSubClient.h>

#include "../include/initPins.hpp"
#include "../include/initWiFi.hpp"
#include "../include/forMQTT.hpp"
#include "../include/config.hpp"

extern PubSubClient client;

uint32_t lastReadDataTime = 0;
uint32_t lastCompressorTurnTime = 0;
bool compressorState = false;
bool compressorStartPosition = true;

void setup() {
    initPins();
    initWiFi();
    initMQTT();
}

void loop() {
    if (!client.connected()) {
        reconnectMQTT();
    }
    else {
        client.loop();
        uint32_t currentReadDataTime = millis();
        if (currentReadDataTime - lastReadDataTime > debounceDelay) {
            lastReadDataTime = currentReadDataTime;
            float temp = dht.readTemperature() - 20;
            float hum = dht.readHumidity();
            // publishSensorData(temp, hum);
            // publishCompressorState(compressorState);
            publishAllData(temp, hum, compressorState);

            if (isnan(temp) || isnan(hum)) {
                lcd.setCursor(0, 0);
                lcd.print("DHT error      ");
                lcd.setCursor(0, 1);
                lcd.print("                ");
            } else {
                lcd.setCursor(0, 0);
                lcd.print("T: ");
                lcd.print(temp, 1);
                lcd.write(byte(0));
                lcd.print("C ");
                lcd.print("H: ");
                lcd.print(hum, 1);
                lcd.print("% ");

                if (temp > tempThreshold) {
                    if (!compressorState)
                        compressorState = true;
                    lcd.setCursor(0, 1);
                    lcd.print("Compressor: ON  ");
                } else {
                    if (compressorState)
                        compressorState = false;
                    lcd.setCursor(0, 1);
                    lcd.print("Compressor: OFF ");
                }
            }
        }

        if (compressorState) {
            uint32_t currentCompressorTurnTime = millis();
            if (currentCompressorTurnTime - lastCompressorTurnTime > delayCompressorTurn) {
                lastCompressorTurnTime = currentCompressorTurnTime;
                if (compressorStartPosition) {
                    compressorServo.write(180);
                    compressorStartPosition = false;
                } else {
                    compressorServo.write(0);
                    compressorStartPosition = true;
                }
            }
        }
    }
}

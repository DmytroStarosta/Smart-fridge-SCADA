#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "../include/forMQTT.hpp"
#include "../include/config.hpp"

extern bool compressorState;

WiFiClient espClient;
PubSubClient client(espClient);

uint32_t lastReconnectMQTT = 0;

void reconnectMQTT() {
    uint32_t currentTimeReconnectMQTT = millis();
    if (currentTimeReconnectMQTT - lastReconnectMQTT > debounceDelayReconnectMQTT) {
        lastReconnectMQTT = currentTimeReconnectMQTT;
        Serial.print("Attempting MQTT connection...");
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            client.publish("outTopic", "hello world");
            client.subscribe("fridge/compressor");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
        }
    }
}

// void publishSensorData(float temperature, float humidity) {
//     Serial.print("Publishing sensor data");
//     char tempStr[8];
//     char humStr[8];
//     dtostrf(temperature, 1, 2, tempStr);
//     dtostrf(humidity, 1, 2, humStr);
//     client.publish("fridge/temperature", tempStr);
//     client.publish("fridge/humidity", humStr);

void publishAllData(float temp, float hum, bool compressor) {
    StaticJsonDocument<200> doc;
    doc["temperature"] = temp;
    doc["humidity"] = hum;
    doc["compressor"] = compressor ? "ON" : "OFF";

    char buffer[200];
    serializeJson(doc, buffer);
    client.publish("fridge/data", buffer);
}
// }

// void publishCompressorState(bool state) {
//     if (state)
//         client.publish("fridge/compressorState", "ON");
//     else
//         client.publish("fridge/compressorState", "OFF");
// }

void callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(String(topic));
    if (String(topic) == "fridge/compressor") {
        if (message == "ON") {
            compressorState = true;
        } else if (message == "OFF") {
            compressorState = false;
        }
    }
}

void initMQTT() {
    client.setServer(MQTT_BROKER, MQTT_PORT);
    client.setCallback(callback);
}

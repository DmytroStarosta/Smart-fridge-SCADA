#ifndef FOR_MQTT_HPP
#define FOR_MQTT_HPP

void reconnectMQTT();
// void publishSensorData(float temperature, float humidity);
// void publishCompressorState(bool state);
void publishAllData(float temp, float hum, bool compressor);
void subscribeMQTT();
void initMQTT();

#endif

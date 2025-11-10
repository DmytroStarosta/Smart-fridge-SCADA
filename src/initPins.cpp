#include "../include/initPins.hpp"
#include "../include/config.hpp"

#define DHTPIN 18
#define DHTTYPE DHT22

byte degreeChar[] = {
    B00111, B00101, B00111, B00000,
    B00000, B00000, B00000, B00000
};

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
Servo compressorServo;

void initPins()
{
    Wire.begin(lcdSDA, lcdSCL);
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, degreeChar);
    lcd.clear();

    dht.begin();

    compressorServo.attach(servoPin);
    compressorServo.write(0);
}

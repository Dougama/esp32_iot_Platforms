#include <WiFiClientSecure.h>
#include <ThingerESP32.h>
#include <Adafruit_BMP085.h>

#define USERNAME "Damaranto"
#define DEVICE_ID "ESP32"
#define DEVICE_CREDENTIAL "oJ6rTT#P7Adz"
#include <Adafruit_BMP085.h>

#define SSID "Halley_LAB"
#define SSID_PASSWORD "H@LLEY2o13"
  
Adafruit_BMP085 bmp;

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(31, OUTPUT);
  
  thing.add_wifi(SSID, SSID_PASSWORD);


  thing["led"] << digitalPin(31);
  thing["Pressure"] >> outputValue(bmp.readPressure()/100.0);
  thing["Temperature"] >> outputValue(bmp.readTemperature());

}

void loop() {
  thing.handle();
  
}

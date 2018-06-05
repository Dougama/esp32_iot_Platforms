// This example shows how to connect to Cayenne using an ESP32 and send/receive sample data.
// Make sure you install the ESP32 Board Package and select the correct ESP32 board before compiling.
// To install the ESP32 Board Package follow the instructions here: https://github.com/espressif/arduino-esp32/blob/master/README.md#installation-instructions.

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
// WiFi network info.
char ssid[] = "Halley_LAB";
char wifiPassword[] = "H@LLEY2o13"; 

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "9362ff10-3440-11e8-96c3-51e4789cd606";
char password[] = "758dde5662c7d3b452407cdd5ade9aec573b6b60";
char clientID[] = "48904130-6778-11e8-8974-21d815a438b9";

unsigned long lastMillis = 0;

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  Cayenne.virtualWrite(32, bmp.readTemperature());
  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  digitalWrite(2, getValue.asInt());
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}



#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
char auth[] = "8a340c24f24145a5a045d3f6e01f4ad9";
char ssid[] = "Halley_LAB";
char pass[] = "H@LLEY2o13";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  delay(100);
  pinMode(2, OUTPUT);
}
float i=0;
void loop()
{
  Blynk.run();
  if (touchRead(T0)<20) {
      digitalWrite(2, HIGH);
      Blynk.virtualWrite(10, i++);
      Blynk.virtualWrite(0,  bmp.readTemperature());
    }
  else digitalWrite(2, LOW);  
  delay(90);
  Serial.println(touchRead(T0));
}



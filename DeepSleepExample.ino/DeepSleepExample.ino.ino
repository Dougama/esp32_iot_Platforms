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

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  3        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

int GREEN_LED_PIN = 2;
int YELLOW_LED_PIN = 2;

void setup(){

  delay(500);
  
  if(bootCount == 0) //Run this only the first time
  {

      bootCount = bootCount+1;
  }else
  {
      pinMode(33, OUTPUT);
  
      thing.add_wifi(SSID, SSID_PASSWORD);
    
    
      thing["led"] << digitalPin(33);
      thing["Pressure"] >> outputValue(bmp.readPressure()/100.0);
      thing["Temperature"] >> outputValue(bmp.readTemperature());


  }
  
  thing.handle();
  delay(3000);

  digitalWrite(GREEN_LED_PIN,LOW);

  //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1)
  esp_deep_sleep_start();
}

void loop(){
  
}

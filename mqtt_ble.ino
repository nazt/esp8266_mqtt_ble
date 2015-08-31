#define MQTT_DEBUG,_MODE
#define WIFI_DEBUG_MODE

#include <WiFiConnector.h>
#include <MqttConnector.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

MqttConnector *mqtt;
WiFiConnector *wifi;


/* MQTT INFO */
#define MQTT_HOST        "iot.eclipse.org"
#define MQTT_PORT        1883
#define PUBLISH_EVERY    20 *1000 // every 20 seconds

/* comment ทิ้งถ้าไม่ส่ username/password */
#define MQTT_USERNAME    "user"
#define MQTT_PASSWORD    "user"

/* SENSOR INFO */
#define DEVICE_NAME "MARQ-001"
#define PROJECT     "MARQ"
#define AUTHOR      "Nat Weerawan"
#define BOARD       "esp-mini.v2"
#define SENSOR      "HM10"

/* WIFI INFO */
#define SSID        "NAT.WRTNODE"
#define PASSPHARSE  "devicenetwork"

#include "init_wifi.h"
#include "_publish.h"
#include "_receive.h"
#include "init_mqtt.h"

byte byteRead;


void init_hardware()
{
  Serial1.begin(115200);
  Serial.begin(115200);
  delay(10);
  Serial.println();

}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();
}

String text = "";
int flag = 0;

void loop()
{
  text = "";
  while (Serial.available()) {
    flag = 1;
    byteRead = Serial.read();
    //Serial.print((char)byteRead);
    text += (char) byteRead;
    delay(10);
    mqtt->loop(wifi);
  }

  if (flag == 1) {
    flag = 0;    
    mqtt->sync_pub(text);
    Serial.print(text);
  }
  mqtt->loop(wifi);
}

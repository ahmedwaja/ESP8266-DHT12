#include <Arduino.h>
#include "DHT12.h"

DHT12 DHT(&Wire);
#define Pin_SLC D1
#define pin_SDA D2

void setup()
{
  Serial.begin(9600);
  DHT.begin(pin_SDA, Pin_SLC);
  int status = DHT.read();
  switch (status)
  {
  case DHT12_OK:
    Serial.println("OK");
    break;
  case DHT12_ERROR_CHECKSUM:
    Serial.println("Checksum error");
    delay(10000);
    ESP.restart();
  case DHT12_ERROR_CONNECT:
    Serial.println("Connect error");
    delay(10000);
    ESP.restart();
  case DHT12_MISSING_BYTES:
    Serial.println("Missing bytes");
    delay(10000);
    ESP.restart();
  default:
    Serial.println("Unknown error");
    delay(10000);
    ESP.restart();
  }
  Serial.println("Temperature / Humidity");
  delay(2000);
}

void loop()
{
  if (millis() - DHT.lastRead() >= 2000)
  {
    DHT.read();
    Serial.println("T : " + String(DHT.getTemperature()) + "\tH : " + String(DHT.getHumidity()));
  }
}
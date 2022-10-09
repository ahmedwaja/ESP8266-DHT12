#include <Arduino.h>
#include "DHT12.h"

DHT12 DHT(&Wire);

void setup()
{
  Serial.begin(9600);
  DHT.begin(D2, D1);
  int status = DHT.read();
  switch (status)
  {
  case DHT12_OK:
    Serial.print("\nOK,\n");
    break;
  case DHT12_ERROR_CHECKSUM:
    Serial.print("\nChecksum error,\n");
    break;
  case DHT12_ERROR_CONNECT:
    Serial.print("\nConnect error,\n");
    break;
  case DHT12_MISSING_BYTES:
    Serial.print("\nMissing bytes,\n");
    break;
  default:
    Serial.print("\nUnknown error,\n");
    break;
  }
  Serial.print("\nTemperature / Humidity\n");
  delay(2000);
}

void loop()
{
  if (millis() - DHT.lastRead() >= 2000)
  {
    DHT.read();
    Serial.print("\nT : ");
    Serial.print(DHT.getTemperature(), 1);
    Serial.print("\tH : ");
    Serial.print(DHT.getHumidity(), 1);
  }
}
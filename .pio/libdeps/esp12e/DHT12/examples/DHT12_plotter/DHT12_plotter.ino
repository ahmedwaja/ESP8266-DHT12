#include <Arduino.h>
#include "DHT12.h"

DHT12 DHT(&Wire);

void setup()
{
  DHT.begin(D2, D1);
  Serial.begin(9600);
  Serial.println("Humidity, Temperature");
  int status = DHT.read();
  switch (status)
  {
  case DHT12_OK:
    Serial.print("OK,\t");
    break;
  case DHT12_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    break;
  case DHT12_ERROR_CONNECT:
    Serial.print("Connect error,\t");
    break;
  case DHT12_MISSING_BYTES:
    Serial.print("Missing bytes,\t");
    break;
  default:
    Serial.print("Unknown error,\t");
    break;
  }
}

void loop()
{
  if (millis() - DHT.lastRead() >= 1000)
  {
    // note no error checking
    DHT.read();
    Serial.print(DHT.getHumidity(), 1);
    Serial.print(", ");
    Serial.println(DHT.getTemperature(), 1);
  }
}

// -- END OF FILE --

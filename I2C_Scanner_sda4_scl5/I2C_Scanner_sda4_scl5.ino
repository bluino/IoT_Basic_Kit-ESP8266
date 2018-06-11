/*
 * Wire - I2C Scanner
 *
 * The WeMos D1 Mini I2C bus uses pins:
 * D1 = SCL
 * D2 = SDA
 */

#include <Wire.h>
#include <ArduinoOTA.h>

const int sclPin = 5;
const int sdaPin = 4;

void setup()
{
  ArduinoOTA.onError([](ota_error_t error) {ESP.restart();});
  ArduinoOTA.begin();
  Wire.begin(sdaPin, sclPin);

  Serial.begin(115200);
  Serial.println("I2C Scanner");
}

void loop()
{
  ArduinoOTA.handle();
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("Done.\n");
  }

  delay(2000);
}

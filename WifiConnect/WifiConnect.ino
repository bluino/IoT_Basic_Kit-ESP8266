/* 
**  Connect the ESP8266 unit to an existing WiFi access point
**  For more information see http://42bots.com
*/

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

// Replace these with your WiFi network settings
const char* ssid = "$your_ssid_maximum_32_characters";
const char* password = "$your_pswd_maximum_32_characters";

void setup()
{
  ArduinoOTA.onError([](ota_error_t error) {ESP.restart();});
  ArduinoOTA.begin();
  delay(1000);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }

  Serial.println("\nsuccess!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
}

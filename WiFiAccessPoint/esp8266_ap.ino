#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ArduinoOTA.h>

const char *ssid = "ESP8266_AP"; // The name of the Wi-Fi network that will be created
const char *password = "$your_pswd_maximum_32_characters";   // The password required to connect to it, leave blank for an open network

void setup() {
  ArduinoOTA.onError([](ota_error_t error) {ESP.restart();});
  ArduinoOTA.begin();
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("Password \"");
  Serial.print(password);
  Serial.println("\"");
  
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
  ArduinoOTA.handle();
  }

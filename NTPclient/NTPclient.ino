#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "$your_ssid_maximum_32_characters";
const char* password = "$your_pswd_maximum_32_characters";

//const char* ssid = "D-Link_DIR-600M";
//const char* password = "12345679";

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 25200, 60000);

void setup(){
  ArduinoOTA.onError([](ota_error_t error) {ESP.restart();});
  ArduinoOTA.begin();
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 250 );
    Serial.print ( "." );
  }
  Serial.println("");

  timeClient.begin();
}

void loop() {
  ArduinoOTA.handle();
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}

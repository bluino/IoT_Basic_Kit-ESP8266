/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
#include <ArduinoOTA.h>


// the setup routine runs once when you press reset:
void setup() {
  ArduinoOTA.onError([](ota_error_t error) {ESP.restart();});
  ArduinoOTA.begin();
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  ArduinoOTA.handle();
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(20);        // delay in between reads for stability
}

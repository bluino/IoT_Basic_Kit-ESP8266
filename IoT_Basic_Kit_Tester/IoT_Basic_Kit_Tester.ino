
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include "images.h"
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define ledPin D0
#define buttonPin1 D1
#define oledSCLPin D2
#define oledSDAPin D3
#define buttonPin2 D4
#define buzzerPin D5
#define relayPin D6
#define rgbPin D8
#define dhtPin D7     

int numPixel = 1;
int delayVal = 1000;
int potPosition;
int buttonStartStatus = 0;
int buttonStopStatus = 0;

#define DHTTYPE    DHT11     // DHT 11
DHT dht(dhtPin, DHTTYPE);

Adafruit_NeoPixel pixels(numPixel, rgbPin, NEO_GRB + NEO_KHZ800);
SSD1306Wire display(0x3c, oledSDAPin, oledSCLPin);

void setup() {
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  
  pixels.begin();
  pixels.setBrightness(30);
  
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  dht.begin();

  pinMode(ledPin, OUTPUT);
  //pinMode(buttonPin1, INPUT_PULLUP);  //if pin use as Button input
  //pinMode(buttonPin2, INPUT_PULLUP);  //if pin use as Button input
  pinMode(buttonPin1, OUTPUT);  //if pin use as LED output
  pinMode(buttonPin2, OUTPUT);  //if pin use as LED output
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
    Oled();
    NeoPixel();
    Relay();
    Blink();
    Buzzer();
    Potensiometer();
    Fade();
    dhtRead();
}


void Blink() {
  int count = 8;
  while(count > 0 ) {
    digitalWrite(buttonPin1, HIGH);
    delay(500);
    digitalWrite(buttonPin1, LOW);
    delay(500);
    count = count -1;
  }
}

void Fade() {
    int count = 4;
    while(count > 0 ) {
      for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
        analogWrite(ledPin, fadeValue);
        delay(30);
      }
    
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
        analogWrite(ledPin, fadeValue);
        delay(30);
      }
      count = count -1;
    }
}

void Potensiometer(){
  int count = 50;
    while(count > 0 ) {
    potPosition = analogRead(A0);
    Serial.println(potPosition);
  
    digitalWrite(buttonPin2, HIGH);
    delay(potPosition);
  
    digitalWrite(buttonPin2, LOW);
    delay(potPosition);
    count = count -1;
  }
}

void Buzzer() {
  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('a', 4);       //birth
  play('g', 4);       //day
  play('C', 4);       //to
  play('b', 4);       //you
  play(' ', 2);       //pause for 2 beats
  play('g', 2);       //ha     
  play('g', 1);       //ppy
  play('a', 4);       //birth
  play('g', 4);       //day
  play('D', 4);       //to
  play('C', 4);       //you
  play(' ', 2);       //pause for 2 beats
  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('G', 4);       //birth
  play('E', 4);       //day
  play('C', 4);       //dear
  play('b', 4);       //your
  play('a', 6);       //name
  play(' ', 2);       //pause for 2 beats
  play('F', 2);       //ha
  play('F', 1);       //ppy
  play('E', 4);       //birth
  play('C', 4);       //day
  play('D', 4);       //to
  play('C', 6);       //you
  delay(3000);
}

void play( char note, int beats) {
  int numNotes = 14;

  char notes[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', ' '};
  int frequencies[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};

  int currentFrequency = 0;
  int beatLength = 150;

  for (int i = 0; i < numNotes; i++) {
    if (notes[i] == note) {
      currentFrequency = frequencies[i];
    }
  }

  tone(buzzerPin, currentFrequency, beats * beatLength);   
  delay(beats* beatLength);
  delay(50);
}


void Relay() {
  /*buttonStartStatus = digitalRead(buttonPin1);
  buttonStopStatus = digitalRead(buttonPin2);

  if (buttonStartStatus == LOW && buttonStopStatus == HIGH) {
    digitalWrite(relayPin, HIGH);
  }

  if (buttonStartStatus == HIGH && buttonStopStatus == LOW) {
    digitalWrite(relayPin, LOW);
  }*/

  int count = 4;
  while(count > 0 ) {
    digitalWrite(relayPin, HIGH);
    delay(1000);
    digitalWrite(relayPin, LOW);
    delay(1000);
    count = count -1;
  }
}

void NeoPixel() {
  pixels.clear();

  //Red color
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();
  delay(delayVal);

  //Green color
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show();
  delay(delayVal);

  //Blue color
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();
  delay(delayVal);

  //Magenta color
  pixels.setPixelColor(0, pixels.Color(0, 255, 255));
  pixels.show();
  delay(delayVal);

  //Yellow color
  pixels.setPixelColor(0, pixels.Color(255, 255, 0));
  pixels.show();
  delay(delayVal);

  //Cyan color
  pixels.setPixelColor(0, pixels.Color(255, 0, 255));
  pixels.show();
  delay(delayVal);

  //White color
  pixels.setPixelColor(0, pixels.Color(255, 255, 255));
  pixels.show();
  delay(delayVal);

  //All off
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay(delayVal);
}

void dhtRead() {
  int count = 10;
 
  while(count > 0 ) {
    delay(2000);
    //read temperature and humidity
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    // clear display
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Temperature: ");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, String(t,1)+" °C");
    
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 30, "Humidity: ");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, String(h,1)+" %");
    
    display.display();
    count = count -1;
  }   
}

void Oled() {
  drawFontFaceDemo();
  delay(2000);
  drawTextFlowDemo();
  delay(2000);
  drawTextAlignmentDemo();
  delay(2000);
  drawImageDemo();
  delay(2000);
}

void drawFontFaceDemo() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
    display.display();
}

void drawTextFlowDemo() {
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128,
    "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
    display.display();
}

void drawTextAlignmentDemo() {
  display.clear();
  display.setFont(ArialMT_Plain_10);

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "Left aligned (0,10)");

  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Center aligned (64,22)");

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, "Right aligned (128,33)");

  display.display();
}

void drawImageDemo() {
    display.clear();
    display.drawXbm(4, 14, Bluino_logo_width, Bluino_logo_height, Bluino_logo_bits);
    display.display();
}

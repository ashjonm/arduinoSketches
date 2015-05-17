#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

int HVAC = 10;
int rLed = 7;
int gLed = 8;
int bLed = 9;

void setup() {
  Serial.begin(9600);
  Serial.println("Thermostat v0.1.0");
  
  pinMode(HVAC, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(gLed, OUTPUT);

  dht.begin();
  
  // Allow the sensor to stablize. 
  flicker(HVAC, 50, 20);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(true);
  float i = dht.computeHeatIndex(t,h);
  int s = (int) (i - 50)/10;
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from sensor!");
    return;
  }
  
  printData(h,t,i,s);
  
  runHVAC(h,t);

  showHeatIndex(s);
}

void printData(float h, float t, float i, int s) {
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("*F\t");
  Serial.print("Index: ");
  Serial.print(i);
  Serial.print("*F\t");
  Serial.print("State: ");
  Serial.println(s);
}

void runHVAC (float h, float t) {
  if ( h > 80 || t > 80) {
    turnOn(HVAC);
  }
  else {
    turnOff(HVAC);
  }
}

void turnOn (int device) {
  digitalWrite(device, HIGH);
}

void turnOff (int device) {
  digitalWrite(device, LOW);
}

void showHeatIndex(int s) {
  triColorLed(s);
}

void flicker(int device, int timeOn, int loops) {
  for (int i = 0; i < loops; i++) {
    ledOn(device, timeOn);
    ledOff(device, timeOn);
  }
}

void ledOn(int device, int timeOn) {
  digitalWrite(device, HIGH);
  delay(timeOn);
}

void ledOff(int device, int timeOff) {
  digitalWrite(device, LOW);
  delay(timeOff);
}

void triColorLed(int state) {
  switch (state) {
    case 0:
      digitalWrite(rLed, LOW);
      digitalWrite(bLed, LOW);
      digitalWrite(gLed, LOW);
      break;
    case 1:
      digitalWrite(rLed, LOW);
      digitalWrite(bLed, LOW);
      digitalWrite(gLed, HIGH);
      break;
    case 2:
      digitalWrite(rLed, LOW);
      digitalWrite(bLed, HIGH);
      digitalWrite(gLed, LOW);
      break;
    case 3:
      digitalWrite(rLed, LOW);
      digitalWrite(bLed, HIGH);
      digitalWrite(gLed, HIGH);
      break;
    case 4:
      digitalWrite(rLed, HIGH);
      digitalWrite(bLed, LOW);
      digitalWrite(gLed, LOW);
      break;
    case 5:
      digitalWrite(rLed, HIGH);
      digitalWrite(bLed, LOW);
      digitalWrite(gLed, HIGH);
      break;
    case 6:
      digitalWrite(rLed, HIGH);
      digitalWrite(bLed, HIGH);
      digitalWrite(gLed, LOW);
      break;
    case 7:
      digitalWrite(rLed, HIGH);
      digitalWrite(bLed, HIGH);
      digitalWrite(gLed, HIGH);
      break;
  }
}

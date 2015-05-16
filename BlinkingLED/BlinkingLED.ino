int led = 10;
int rLed = 7;
int bLed = 8;
int gLed = 9;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(gLed, OUTPUT);
}

void loop() {
  for (int i = 1; i<8; i++) {
    flicker(led, 75, 7);
    triColorLed(i);
    delay(8000);
    triColorLed(0);
    flicker(led, 1000, 5);
  }
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

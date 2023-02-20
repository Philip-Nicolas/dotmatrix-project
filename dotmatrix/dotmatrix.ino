#include "images.h"

const int dataPin = 4;
const int clockPin = 2;
const int latchPin = 3;

const int potPin = A0;

int min_pot_reading = 128;

byte data = B10010110; //example image

void serialWrite2(byte data1, byte data2) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data1);
  shiftOut(dataPin, clockPin, LSBFIRST, data2);
  digitalWrite(latchPin, HIGH);
}

void scanImage(byte img[8]) {
  for (int i = 0; i < 8; i++){
    serialWrite2(img[i] ^ B11111111, B00000001 << i);
    delay(map(max(analogRead(A0), min_pot_reading), min_pot_reading, 1023, 0, 200));
  }
}

void setup() {
  pinMode(potPin, INPUT);
  
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  scanImage(gojuryu);
}

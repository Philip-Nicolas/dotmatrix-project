const int dataPin = 4;
const int clockPin = 2;
const int latchPin = 3;

byte data = B10010110; //example image

void serialWrite(byte data) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  serialWrite(data);
}

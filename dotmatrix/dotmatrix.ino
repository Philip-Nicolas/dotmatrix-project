const int dataPin = 4;
const int clockPin = 2;
const int latchPin = 3;

const int potPin = A0;

int min_pot_reading = 128;
int dt = 1;

byte data = B10010110; //example image

void serialWrite2(byte data1, byte data2) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data1);
  shiftOut(dataPin, clockPin, LSBFIRST, data2);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  pinMode(potPin, INPUT);
  
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  dt = map(max(analogRead(potPin), min_pot_reading), min_pot_reading, 1023, 0, 200);
  
  serialWrite2(data, data ^ B11111111);
  delay(dt);
  serialWrite2(data ^ B11111111, data);
  delay(dt);
}

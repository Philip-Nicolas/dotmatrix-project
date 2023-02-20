#include "images.hpp"
#include "animation.hpp"

#define scanlines 8

const int dataPin = 4;
const int clockPin = 2;
const int latchPin = 3;

// animation constants. see animation.hpp for animation.
const int fps = 12;
const int duration = frames * 1000 / fps; // animation duration in ms
int frame = 0; // index of frame to be currently drawn

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  // setup timer1
  /*
   * TCCR1A: Timer/Counter Control Register (1) A
   *           * mode select
   *           * WGM set (partial)
   * TCCR1B: Timer/Counter Control Register (1) B
   *           * input settings
   *           * WGM set (partial)
   *           * prescaler select
   * TIMSK1: Timer Interrupt MaSK (1)
   *         enables/disables interrupts associated with this timer
   * 
   * WGM   : Waveform Generation Mode
   */
  TCCR1A = bit(WGM10); // 8-bit mode
  TCCR1B = bit(CS11) | bit (CS10); // sets prescaler to 64, roughly 1 refresh / 14ms
//  TCCR1B = bit(CS11); // sets prescaler to 8, roughly 1 refresh / 1.6ms
//  TCCR1B = bit(CS10); // sets prescaler to 1, roughly 1 refresh / 4us (too fast, since refresh takes ~260us)
  TIMSK1 |= bit(TOIE1); // enable overflow interrupt
}

byte draw[scanlines];
volatile uint8_t scanline = 0;

// Interrupt service run when Timer/Counter1 OVERFLOW
ISR(TIMER1_OVF_vect) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, draw[scanline] ^ B11111111);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000001 << scanline);
  digitalWrite(latchPin, HIGH);
  
  if (scanline >= scanlines) {
    scanline = 0;
  } else {
    scanline++;
  }
}

/*
 * Updates the image being drawn on the display.
 * This is where pixel shaders would get applied.
 */
void updateDisplay(byte newImage[scanlines]) {
  for (uint8_t i = 0; i < scanlines; i++) {
    draw[i] = newImage[i];
  }
}

void loop() {
  frame = (millis() % (duration * 2)) * frames / duration - frames;
  updateDisplay(animation[max(0, abs(frame + 1) - 1)]);
}

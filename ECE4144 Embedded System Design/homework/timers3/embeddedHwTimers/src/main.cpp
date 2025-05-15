#include <Arduino.h>
// use timer1, 16 bit
// PWM frequency is 1kHz



#define MAX_DUTY 100 // from 0 to 100


void setup() {
  // put your setup code here, to run once:

  DDRB |= (1 << 6); // OC1B
  // leave channel a and c
  // use channel b for OCR1B
  // OCR1A is set at top
  TCCR1A = 0b00100011;
  TCCR1B = 0b00011001; // no prescaling
  TCCR1C = 0;

  OCR1A = 7988;

  OCR1B = 3990;
  // OCR1B = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  OCR1B++;
  delay(1);

// prevent integer overflow 79.88
  if ((OCR1B >= ((MAX_DUTY * 79.88))) || (OCR1B == OCR1A)){
    OCR1B = 0;  
  }


}


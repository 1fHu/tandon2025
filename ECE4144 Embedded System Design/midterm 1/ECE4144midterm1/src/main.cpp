#include <Arduino.h>

// put function declarations here:
void adc_init (void){
  ADMUX = 0b01000010; // aVcc selected, 100010(ADC10) used, input D6

  ADCSRA = 0b10000011; 
  // enabled, not start yet, no trigger, no interrupt, 8 clk prescale
  ADCSRB = 0b00100000; // no high speed, mux set, free running
  DIDR2 = 0; // sleep when needed
}

void pwm_init(void){
  TCCR1A = 0b00100011; // channel A timer 1 OCR1A on top, fast pwm
  TCCR1B = 0b00011010; // 1MHz clk need 8 prescaler
  TCCR1C = 0;

  OCR1A = 0; 
  OCR1B = OCR1A / 2; 

  DDRB |= (1<<6); // PB6, IO 10 for output
}

int readAdc(char chan)
{
    ADMUX = (1 << REFS0) | (chan & 0x0F);

    ADCSRA |= (1 << ADSC); // start

    while (ADCSRA & (1 << ADSC)); // Wait 

    return ADCW; // 16-bit register 

}

// period max: 0.52428, unit: second
void pwm_fix(double period){
  OCR1A = period * 125000;
  OCR1B = OCR1A / 2;
}

void setup() {
  // run once:
  adc_init();
  pwm_init();

}

void loop() {
  // run repeatedly:
  int adc_value = readAdc(13);

  if (adc_value <= 155 ){ // less than 0 C
    pwm_fix(0.5);
  }
  else if (adc_value >= 310){ // more than 50 C
    pwm_fix(0);
  }
  else{ // between 0 and 50 C
    double period1 = (adc_value * 0.5) / 1023;
    pwm_fix(period1);
  }

  delay(50);
}

// put function definitions here:

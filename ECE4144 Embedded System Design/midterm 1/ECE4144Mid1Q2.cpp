#include <Arduino.h>

// function declarations:
void adc_init(void);
int readAdc(void);
void pwm_init(void);
void pwm_adjust(double period);



void setup() {
  // run once:
  adc_init();
  pwm_init();
  // Serial.begin(9600);
}

void loop() {
  // run repeatedly: 
  
  int adc_value = readAdc();
  // Serial.println("ADC Read: ");
  // Serial.println(adc_value);
  double pwm_period = adc_value * 0.000488759;
  // Serial.println("pwm Period: ");
  // Serial.println(pwm_period);
  pwm_adjust(pwm_period);

}

// function definitions: 

void adc_init(void)
{
  ADMUX = 0b01000111; // 000111 (ADC7)
  ADCSRA = 0b10000110;
  ADCSRB = 0;
}

int readAdc(void)
{
  ADCSRA |= (1<<ADSC); // start conversion
  delay(50);
  while (ADCSRA & (1<<ADSC)); // Wait for the conversion to complete.
  return ADCW;
}

void pwm_init(void){
    TCCR1A = 0b00100011; // channel b out, 1111
    TCCR1B = 0b00011100; // 256 presclar 
    OCR1A = 31252;
    OCR1B = OCR1A / 2;
    DDRB |= (1<<6); // PB6, IO 10 for output
}

// period (0-0.5) second
void pwm_adjust(double period){
    int clip = period * 62504;
    OCR1B = clip;
    OCR1B++;
    if (OCR1B >= OCR1A){
      OCR1B = 0;  
    }
}
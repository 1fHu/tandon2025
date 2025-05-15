#include <Arduino.h>
void setup() {
// run once:
Serial.begin(9600);

// pwm timer 0 fast pwm, 1khz, OCRA top
TCCR0A = 0b00100011;
TCCR0B = 0b00001011; // 64 presclar

OCR0A = 125;
OCR0B = 0;
// output 
DDRD |= ( 1 << 0);

// ADC
ADMUX = 0b01000001; // 100001
ADCSRA = 0b11100111; // 128 pre
ADCSRB = 0b00100000;
DIDR2 |= (1 << 1);
}
void loop() {
// run repeatedly:
float aval;
long x;
x = millis();
aval =abs(3 * sin(2 * 3.141592654 * x / 1000));
delay(1);

// pwm duty

delay(20);
OCR0B = aval * (OCR0A / 3);

Serial.println(aval);

unsigned short *ADCData;
unsigned short ADCVal;
ADCData=(unsigned short *)0x78;
ADCVal=(*ADCData & 0x3FF);

float fADCVal;
fADCVal=((float)ADCVal)/1023 * 3; 

Serial.print(abs(aval)); //Original rectified sinusoid
Serial.print(" ");
Serial.println(fADCVal); //Analog voltage measured from ADC

}
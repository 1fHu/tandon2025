#include <Arduino.h>


//Q1

void adc_init(void)
{
ADMUX = (1 << REFS0); // voltage set as AVcc on the top measurement
ADCSRA = (1 << ADEN) | 7; // ADC enabled, prescaler bits set as 128
}

int readAdc(char chan)
{
ADMUX = (1<<REFS0) | (chan & 0x0f); // AVcc as voltage source, use chan to select ADC Channel
ADCSRA |= (1<<ADSC); // start conversion
while (ADCSRA & (1<<ADSC)); // Wait for the conversion to complete.
return ADCW; // ADCW is the 16-bit register containing the result of the ADC conversion, 
// it combines ADCL and ADCH
}

// Q2
uint8_t *ptrADMUX = (uint8_t*)0x7C;
uint8_t *ptrADCSRA = (uint8_t*)0x7A;
uint16_t *ptrADCW = (uint16_t*)0x78;

void adc_init_no_macros(void){
*ptrADMUX |= (1 << 6);
*ptrADCSRA |= (1 << 7) | (1 << 0) | (1 << 1) | (1 << 2);
}
int readAdc_no_macro(char chan){
  *ptrADMUX |= (1 << 7) | (chan & 0x0F);
  *ptrADCSRA |= (1 << 6);
  while (*ptrADCSRA & ( 1 << 6));
  return *ptrADCW;
}

//Q3

void setup() {
  // put your setup code here, to run once:
  adc_init();

pinMode(4, OUTPUT);
digitalWrite(4, LOW); 

// Serial.begin(9600);
}

bool led = false;

void loop() {
  // put your main code here, to run repeatedly:
  
  
  // if the analog voltage on A0 is greater than 1.0V, LED connect to pin 4 should be on
  // LED off otherwise
  int adcValue = readAdc(0);
  if (adcValue > 210){

    led = true;
  }
  else if (adcValue <200)

  { // manage LED cycling if the voltage hovers around 1.0V
    led = false;
  }

  digitalWrite(4, led ? HIGH : LOW);

  delay (50);
  // Serial.print(">light:");
  // Serial.println(adcValue);
}

int answer  = analogRead()

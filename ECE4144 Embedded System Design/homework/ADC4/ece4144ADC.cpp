#include <Arduino.h>

//Q1
void adc_init(void) 
{
    ADMUX = (1 << REFS0); // sets the voltage reference to AVCC and tells the ADC hardware to measure analog voltage.

    ADCSRA = (1 << ADEN) | 7; // enables the ADC system itself, sets the ADC prescaler bits (ADPS2, ADPS1, ADPS0) to divide the CPU clock by 128.
}


int readAdc(char chan)
{
    ADMUX = (1 << REFS0) | (chan & 0x0F); // Reconfigure ADMUX so that the voltage reference is AVCC (REFS0=1),
    // and select the ADC channel given by 'chan' (0–15).

    ADCSRA |= (1 << ADSC); // Setting ADSC (ADC Start Conversion) to 1 begins an ADC conversion.

    while (ADCSRA & (1 << ADSC)); // Wait for the conversion to complete. 

    return ADCW; // ADCW is the 16-bit register containing the result of the ADC conversion,
    // it combines ADCL and ADCH 

}

// Q2

#define ADMUX_ADDR   0x7C
#define ADCSRA_ADDR  0x7A
#define ADCL_ADDR    0x78
#define ADCH_ADDR    0x79


#define ADEN_BIT  7   
#define ADSC_BIT  6   


#define REFS0_BIT 6   


volatile uint8_t *pADMUX   = (uint8_t *)ADMUX_ADDR;
volatile uint8_t *pADCSRA  = (uint8_t *)ADCSRA_ADDR;
volatile uint8_t *pADCL    = (uint8_t *)ADCL_ADDR;
volatile uint8_t *pADCH    = (uint8_t *)ADCH_ADDR;


void adc_init_no_macros(void)
{

    *pADMUX = (1 << REFS0_BIT);
    *pADCSRA = ( (1 << ADEN_BIT) | 0x07 );
}


int readAdc_no_macros(char chan)
{

    *pADMUX = (1 << REFS0_BIT) | (chan & 0x0F);
    *pADCSRA |= (1 << ADSC_BIT);

    while ( (*pADCSRA) & (1 << ADSC_BIT) ){}

   
    uint16_t result = *pADCL;        
    result |= ( ((uint16_t)*pADCH) << 8 ); 

    return result;
}
 
//Q3

const int LED_PIN = 4;
const int ANALOG_CHANNEL = 0;
const int THRESHOLD_HIGH = 210;  
const int THRESHOLD_LOW  = 200;  


bool ledState = false;



void setup()
{
    
    adc_init(); 

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);  
}

void loop()
{
    
    int adcValue = readAdc(ANALOG_CHANNEL);


    if (adcValue > THRESHOLD_HIGH)
    {
        ledState = true;  
    }
    else if (adcValue < THRESHOLD_LOW)
    {
        ledState = false; 
    }

    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    delay(50);
}

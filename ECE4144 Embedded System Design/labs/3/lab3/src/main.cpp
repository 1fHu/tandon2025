#include <Arduino.h>

const int ledPin = PC7;    // LED connected to PB0
const int buttonPin = PD4; // Right button connected to PD4


// my code, team A

void setup() {

  UCSR1A = 0b00000000; // normal speed
  
  UCSR1C = 0b00000110; // 8 bit
  UBRR1 = 51; 
  UCSR1B = 0b10011000; // RX Interrupt, receiver, transmitter

  DDRC |= (1 << ledPin); // LED DDRD, output on
  
  DDRD &= ~(1 << buttonPin); // logic 0 as input 
  PORTD |= (1 << buttonPin); // using pull up resistor to prevent floating when unconnected

  sei(); // enable global interrupts
}


void loop() {
  if ((PIND & ( 1 << buttonPin)) != 0) {
    while (!(UCSR1A & (1 << UDRE1))) {} 
    uint8_t d = '1';
    UDR1 = d; 
  } else {
    while (!(UCSR1A & (1 << UDRE1))) {} 
    uint8_t d = '0';
    UDR1 = d;
  }
}

volatile uint8_t rx = 0;
ISR (USART1_RX_vect) {
  rx = UDR1;
  if (rx == 0x31){
    PORTC |= (1 << ledPin); // Turn ON LED
  }
  else if (rx == 0x30){
    PORTC &= ~(1 << ledPin); // Turn OFF LED
  }
}



// my team B code practice

void setup() {

  UCSR1A = 0b00000000; // normal speed
  
  UCSR1C = 0b00000110; // 8 bit
  UBRR1 = 51; 
  UCSR1B = 0b10011000; // RX Interrupt,  receiver, transmitter

  DDRC |= (1 << ledPin); // LED DDRD, output on
  
  sei(); // enable global interrupts
}

volatile uint8_t rx = 0;

ISR (USART1_RX_vect) {
  rx = UDR1;
  if (rx == 0x31){
    PORTC |= (1 << ledPin); // Turn ON LED 
  }
  else if (rx == 0x30) {
    PORTC &= ~(1 << ledPin); // Turn OFF LED
  }

  // send info back to team A
  while (!(UCSR1A & (1 << UDRE1))) {} 
  UDR1 = rx;
}

void loop(){

}


/*
// others code for team B
#include <Arduino.h>
#include <avr/interrupt.h>

ISR(USART1_RX_vect) {
  uint8_t receivedByte = UDR1;

  if (receivedByte == 1) {

    PORTC |= (1 << PC7);    // Turn LED on
  } else {

    PORTC &= ~(1 << PC7);   // Turn LED off
  }
  
  // Send confirmation: transmit the same byte back to Team A.
  while (!(UCSR1A & (1 << UDRE1))) { }
  UDR1 = receivedByte;
}

void setup() {
  UCSR1A=0b00000010;
  UCSR1B=0b10011000;
  UCSR1C=0b00000110;
  UBRR1 = 51;
  
  DDRC |= (1 << PC7);
  // Enable global interrupts.
  sei();

}

void loop() {
}

*/
/*
// others code for team A

#include <avr/interrupt.h>

volatile uint8_t teamBStatus = 0;

ISR(USART1_RX_vect) {
  uint8_t receivedByte = UDR1; 
  teamBStatus = receivedByte;
  
  if (teamBStatus == 1) {
    PORTC |= (1 << PC7);    // Turn LED on
  } else {
    PORTC &= ~(1 << PC7);   // Turn LED off
  }
}

void setup() {
  UCSR1A = 0b00000010;
  UCSR1B = 0b10011000;
  UCSR1C = 0b00000110;
  UBRR1 = 51;
  
  DDRC |= (1 << PC7);
  DDRF &= ~(1 << PF6);
  sei();
}

void loop() {
  if (PINF & (1 << PF6)) {
    while (!(UCSR1A & (1 << UDRE1))) { } 
    UDR1 = 1;
  } else {
    while (!(UCSR1A & (1 << UDRE1))) { }
    UDR1 = 0;
  }
  delay(10); 
}


*/
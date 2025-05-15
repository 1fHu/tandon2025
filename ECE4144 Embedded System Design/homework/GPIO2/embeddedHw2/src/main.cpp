#include <Arduino.h>

// D1 - LED 1 
// D2 - LED 2
// D3 - LED 3 
// D4 - Left button for start and stop a counter
// F6 - right button for reset
// C7 - red LED shows whether button is pressed

bool run = false;
uint8_t counter = 0;

void setup() {
  // set D1,2,3 to an output by setting DDRD
  DDRD |= (1 << 1) | (1 << 2) | (1 << 3);

  // DDR (buttons) set to zero for input
  DDRD &= ~(1 << 4); 
  DDRF &= ~(1 << 6); 

  // initialize all LED OFF by portD
  PORTD &= ~((1 << 1) | (1 << 2) | (1 << 3));

  // red led on board shows button pressed
  DDRC |= (1<<7);
}


void loop() {

  delay(10); // make sure button press can be detected by hardware
  if ((PIND & (1 << 4)) != 0){ // pause button pressed
    while ((PIND & (1 << 4)) != 0);
    // delay(100);
    PORTC |= (1<<7); 
    run = !run;
    delay(200);
    PORTC &= ~(1<<7);
  }
  else if ((PINF & (1 << 6)) != 0){ // reset button pressed
    while ((PINF & (1 << 6)) != 0);
    // check for light
    PORTC |= (1<<7); 
    delay(200);
    PORTC &= ~(1<<7);

    counter = 0;
    PORTD &= ~((1 <<1) | (1 << 2) | (1 << 3)); // turn off all LED
  }
  else{
    delay(500); // easy for detect button pressed
  }

  if (run){
    // set all light on, then off, 
    // then on and compare with three binary numbers, light correct
    PORTD = (PORTD & ~((1 << 1) | (1 << 2) | (1 << 3))) | ((counter & 0x07) << 1);
    counter ++;
    if (counter >= 8) counter = 0; // reset
    delay (500); 
  }
}


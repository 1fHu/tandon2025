/*
Use this code it your board is not detected by computer, 
or its reset button is not working.
Quickly tap reset button twice, during the red LED blinking
window, upload this code to it. 
*/


#include <Arduino.h>



void setup() {
    pinMode(13, OUTPUT);
   
}
  
  void loop() {
    digitalWrite(13, HIGH); // blink onboard LED to confirm recovery
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }
#include <Arduino.h>


void USART_Init(){
  UCSR1A = 0b00100000; // Data Register Empty Interrupt
  UCSR1C = 0b00000110; // 8 bit 
  UBRR1 = 3; // 115.2k
  // UCSR1B = 0b10010000; // RX Complete Interrupt Enable, Receiver Enable
  UCSR1B = 0b10011000; // RX Complete Interrupt Enable, Receiver Enable, Transmitter Enable
}

/*
void TransmitString(const char* str, uint8_t length){
  for (int i = 0; i < length ; i++){
    while (!(UCSR1A & ( 1 << UDRE1)));
      UDR1 = str[i];
  }
}

void setup() {

  USART_Init();
  // Serial1.begin(115200, SERIAL_8N1);
  // TransmitString("UART initialized\n", 17);
}

ISR(USART1_RX_vect){
  char received = UDR1;
  switch (received) {
    case '1':
      TransmitString("One\n", 4);
      break;
    case '2':
      TransmitString("Two\n", 4);
      break;
    default:
      TransmitString("Default\n", 8);
      break;
  }

}


void loop() {

}
*/

/**/
void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for USB connection (important for ATmega32U4)
}

void loop() {
  if (Serial.available()) {
    char received = Serial.read();

    switch (received) {
      case '1':
        Serial.print("One\n");
        break;
      case '2':
        Serial.print("Two\n");
        break;
      default:
        Serial.print("Default\n");
        break;
    }
  }
}

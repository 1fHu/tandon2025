#include <Arduino.h>
#include <Wire.h>

// use INT2


// slave 7-bit adddress
// 0xAE -> 0b10101110 -> 0b1010111 (0x57)
uint8_t SLA_ADDRESS = 0b1010111;


// use LED RED PC7
const int ledPin = PC7;



void setup() {
// LED
DDRC |= (1 << ledPin); // DDR, output on

// sensor set up
Wire.begin();
Wire.beginTransmission(SLA_ADDRESS); 
Wire.write(0x01); 
Wire.write(0b00010000); // bit 4, enable SPO2 Interrupt
Wire.endTransmission();

Wire.beginTransmission(SLA_ADDRESS); 
Wire.write(0x06); 
Wire.write(0b00000011); // bit 2:0 = 011, enable SPO2
Wire.endTransmission();

Wire.beginTransmission(SLA_ADDRESS); 
Wire.write(0x07); 
Wire.write(0b00000000); // leave default
Wire.endTransmission();

// I2C/TWI
TWSR = 0;  // prescaler = 1
TWBR = 32; // frequency = 100 kHz
TWCR = (1 << TWEN); // enable TWI

// INT2 for external interrupt
EIMSK |= (1 << INT2);
EICRA |= (1 << ISC21); // 0b00100000 falling edge of INT2 call interrupt
EICRA &= ~(1 << ISC20); 
EIFR |= (1 << INTF2); // Clear any pending INT2

sei(); // enable global interrupts

Serial.begin(9600); // for data present
}

// use struct easy to return ir and red data
struct Sample{
    uint16_t ir;
    uint16_t red;
};


// Get one sample data, return in Struct Sample Type
Sample GetData(){
// prepare number of samples needs to read
Wire.beginTransmission(SLA_ADDRESS);
Wire.write(0x02); // FIFO_WR_PTR register
Wire.endTransmission(false); // restart
Wire.requestFrom(SLA_ADDRESS, 1);
uint8_t fifoWrPtr = Wire.read(); 


Wire.beginTransmission(SLA_ADDRESS);
Wire.write(0x04); // FIFO_Rd_PTR register
Wire.endTransmission(false); // restart
Wire.requestFrom(SLA_ADDRESS, 1);
uint8_t fifoRdPtr = Wire.read(); 

// multiple samples to read if needed
int numAvaSamples = fifoWrPtr - fifoRdPtr; 
if (numAvaSamples < 0) numAvaSamples += 16; // handle negative
uint8_t numSamplesToRead = numAvaSamples; 

// read one sample 
Wire.beginTransmission(SLA_ADDRESS);
Wire.write(0x05); // FIFO_DATA register
Wire.endTransmission(false); 
Wire.requestFrom(SLA_ADDRESS, 4);
uint8_t ir_high = Wire.read(); 
uint8_t ir_low = Wire.read();
uint8_t red_high = Wire.read();
uint8_t red_low = Wire.read();

Sample oneSam = {0, 0};
oneSam.ir = ((uint16_t)ir_high << 8) | (ir_low);
oneSam.red = ((uint16_t)red_high << 8) | red_low;

return oneSam; 

}



ISR(INT2_vect){
    Sample gotOneSam = {0, 0};
    gotOneSam = GetData(); // received data and store it
    Serial.print("IR (short): ");
    Serial.println((short)gotOneSam.ir);  // cast to short
    Serial.print("RED (short): ");
    Serial.println((short)gotOneSam.red);

    PORTC |= (1 << ledPin); // Turn ON LED 
    delay(300);
    PORTC &= ~(1 << ledPin); // Turn OFF LED
    delay(500);

}

void loop() {

}


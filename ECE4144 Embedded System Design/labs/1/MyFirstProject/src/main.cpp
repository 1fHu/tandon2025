#include <Arduino.h>
void NewDelay (unsigned long mSecondsApx);
void setup()
{
Serial.begin(9600);
unsigned char *portDDRC;
portDDRC = (unsigned char *) 0x27;
*portDDRC |= 0x80;
}
void loop ()
{
unsigned char *portC;
portC = (unsigned char *) 0x28;
*portC |= 0x80;
Serial.println("LED OFF");
NewDelay (100);
*portC &= 0x7F;
Serial.println("LED OFF");
NewDelay (100);
}
void NewDelay (unsigned long mSecondsApx)
{
volatile unsigned long i;
unsigned long j = 0;
unsigned long endTime = 100 * mSecondsApx;
i= 0;
while (j == 0)
{
i++;
if (i == endTime)
{
j = 1;
}
}
}
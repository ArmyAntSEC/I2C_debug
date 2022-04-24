#include <Arduino.h>
#include <Wire.h>
#include <SerialStream.h>
int LED = 13;
volatile int x = 0;

#define master

volatile int8_t riseCount = 0;

void riseDetected()
{
    riseCount++;
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) {}

    Log << "*************************" << endl;
    Log << "Hello I2C World!" << endl;

    pinMode( 2, INPUT_PULLUP );
    attachInterrupt( digitalPinToInterrupt(2), riseDetected, RISING );

    delay(100);

    Wire.begin();
    Wire.beginTransmission(9); 
    Wire.write("Hello World!");                     
    Wire.endTransmission();    

    
}

void loop()
{
    int16_t myRiseCount;
    noInterrupts();
    myRiseCount = riseCount;
    interrupts();
    Log << "Rise count: " << myRiseCount << endl;
    delay(500);

    Wire.beginTransmission(9); 
    Wire.write("Hello World!");                     
    Wire.endTransmission();    
}
#include <Arduino.h>
#include <Wire.h>
#include <base.h>
int LED = 13;
volatile int x = 0;

#define master

void receiveEvent(int bytes) {
  x = Wire.read();
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) {}

    Log << "*************************" << endl;
    Log << "Hello I2C World!" << endl;

#ifdef master
    Log << "I am master!!!" << endl;
    Wire.begin();
#else
    Log << "I am slave!!!" << endl;
    pinMode (LED, OUTPUT);  
    Wire.begin(9);   
    Wire.onReceive(receiveEvent);
#endif
}

void loop()
{
#ifdef master
    Wire.beginTransmission(9); 
    Wire.write(x);             
    Wire.endTransmission();    
    x++;                       
    if (x > 5)
        x = 0;
    delay(500);
#else
    if (x == '0') {
        digitalWrite(LED, HIGH);
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);
    }

    if (x == '3') {
        digitalWrite(LED, HIGH);
        delay(400);
        digitalWrite(LED, LOW);
        delay(400);
    }
#endif
}
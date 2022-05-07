#include <Arduino.h>
#include <Wire.h>
#include <SerialStream.h>
int LED = 13;
volatile int x = 0;

#define master

bool ledOn = false;

void onReceive( int n )
{
    ledOn = !ledOn;
    digitalWrite( 13, ledOn );
    Serial.println( "Data received" ); 
    while(Wire.available() > 0 ) 
    {
        char c = Wire.read(); 
        Serial.print(c);      
    }    
    Serial.println();      
}

void onRequest( )
{
    Serial.println( "Data requested" );     
    Wire.write( "OK" );
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) {}

    Log << "*************************" << endl;
    Log << "Hello I2C World!" << endl;

    delay(1000);

    #ifdef master
        Wire.begin();    
    #else
        Wire.begin(8);     
        Wire.onRequest(onRequest);
        Wire.onReceive(onReceive);
        pinMode( 13, OUTPUT );
    #endif

    
}

void loop()
{    
    #ifdef master
        Serial.print ( "::" );
        Wire.beginTransmission(8); 
        Wire.write("Hello World!");                     
        Wire.endTransmission();                                    
        int n = Wire.requestFrom(8, 2);
        Serial.print ( n );
        while ( Wire.available() ) {
            char c = Wire.read();
            Serial.print( c );    
        }
        Serial.println();        
        delay(250);
    #else              
    #endif
    
}
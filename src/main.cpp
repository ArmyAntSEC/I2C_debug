#include <Arduino.h>
#include <Wire.h>
#include <SerialStream.h>
int LED = 13;
volatile int x = 0;

#define master
#define ID 9

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
    Log << "Hello I2C World" << endl;
    #ifdef ID
        Log << "ID: " << ID << endl;
    #else
        Log << "Master" << endl;
    #endif

    pinMode( 13, OUTPUT );
    
    delay(1000);

    #ifdef master
        Wire.begin();    
    #else
        Wire.begin(ID);     
        Wire.onRequest(onRequest);
        Wire.onReceive(onReceive);
        
    #endif

    
}

void loop()
{    
    #ifdef master
        Serial.print ( millis() );
        Serial.print ( "::" );
        Wire.beginTransmission(9); 
        Wire.write("Hello World!");                     
        Wire.endTransmission();                                    
        int n = Wire.requestFrom(9, 2);
        Serial.print ( n );
        while ( Wire.available() ) {
            char c = Wire.read();
            Serial.print( c );    
        }
        Serial.println();        
        ledOn = !ledOn;
        digitalWrite( 13, ledOn );
        
        delay(250);
        
    #else              
    #endif
    
}
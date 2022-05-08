#include <Arduino.h>
#include <Wire.h>
#include <SerialStream.h>
int LED = 13;
volatile int x = 0;

//#define master
#define ID 9

bool ledOn = false;

int32_t command[3] = {1, 1234, 2e6 };

void onReceive( int n )
{
    ledOn = !ledOn;
    digitalWrite( 13, ledOn );
    Serial.println( "Data received" ); 

    uint8_t* commandBytes = (uint8_t*)(command);    

    for ( int i = 0; i < sizeof(command) & Wire.available() > 0; i++ ) {
        commandBytes[i] = Wire.read();         
    } 
    
    for ( int i = 0; i < 3; i++ ) {
        Serial.print( command[i] );
        Serial.print ( " " );    
    }
    Serial.println();          
}

void onRequest( )
{
    Serial.println( "Data requested" );     
    Wire.write( 1 );
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
        Wire.beginTransmission(ID); 
        for ( int i = 0; i < sizeof(command); i++ ) {
            uint8_t* commandBytes = (uint8_t*)(command);
            Wire.write( commandBytes[i] );
        }
        Wire.endTransmission();                                    
        int n = Wire.requestFrom(ID, 1);
        Serial.print ( n );
        Serial.print ( " " );
        while ( Wire.available() ) {
            char c = Wire.read();
            Serial.print( c );    
        }
        Serial.println();        
        ledOn = !ledOn;
        digitalWrite( 13, ledOn );
        
        delay(2000);
        
    #else              
    #endif
    
}
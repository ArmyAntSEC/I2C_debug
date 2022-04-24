#pragma once
#include <base.h>

#define PRINTVAR(var) " " << #var << ": " << var

enum _EndlCode { endl };

class SerialStream
{
  
public:
  template<class T>
  SerialStream& operator<< ( T arg )
  {    
    #ifdef ARDUINO
    Serial.print ( arg );
    #else
    std::cout << arg;
    #endif
    
    return *this;
  }
    
  SerialStream& operator<< (  _EndlCode )
  {
    #ifdef ARDUINO
    Serial.println ();
    #else
    std::cout << std::endl;
    #endif

    return *this;
  }
  
};
  
extern SerialStream SerialLog;

#ifdef ARDUINO
#define Log SerialLog << "[" << millis() << "]: "
#else
#define Log SerialLog
#endif  
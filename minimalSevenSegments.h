#ifndef __SBELL_SEVEN_SEGMENT_H__
#define __SBELL_SEVEN_SEGMENT_H__

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#define NUMBER_SEGMENTS 8

class SingleSevenSegment {

    const byte _alpha_offset = 10;
          byte _pins[NUMBER_SEGMENTS];
          byte _on;
          byte _off;

    inline byte 
    getVoltage(byte bn, byte i) { return (bn & (1 << i) ? _on : _off); }

    void clean();

  public:
    SingleSevenSegment() {}

    void begin( byte pins[], byte on = HIGH, byte off = LOW);

    void setSymbol(char c);
    void setSymbol(byte n);
    void setSymbol(int n);

};

#endif

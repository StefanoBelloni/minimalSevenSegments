// #define DEBUG_ARDUINO 1

#include "minimalSevenSegments.h"

#if DEBUG_ARDUINO
  #define DEBUG_INIT() Serial.begin(9600)
  #define DEBUG(_val_) Serial.print((_val_))
  #define DEBUGLN(_val_) Serial.println((_val_))
#else
  #define DEBUG_INIT()
  #define DEBUG(_val_)
  #define DEBUGLN(_val_)
#endif

/* ==================================================================== */

SingleSevenSegment sss;
byte pins[] = {6, 5, 2, 3, 4, 7, 8, 9};

/* ==================================================================== */

void _delay(unsigned long ms)
{
  unsigned long firstMillis = millis();
  while ( millis() - firstMillis < ms ) {}
}


void cycleSegments(int delayTime) {
  _delay(delayTime * 3);
  sss.setSymbol(' ');

  byte max_num = 16;
  for (byte i = 0; i <= max_num; ++i) {
    _delay(delayTime * 3);
    sss.setSymbol(i);
  }
  char c = 'A';
  sss.setSymbol(' ');
  _delay(delayTime * 6);
  for ( ; c <= 'z'; ++c ) {
    sss.setSymbol(c);
    _delay(delayTime);
  }
}

/* ==================================================================== */

void setup() {
  // put your setup code here, to run once:
  sss.begin(pins);
  DEBUG_INIT();

}

void loop() {
  // put your main code here, to run repeatedly:
  cycleSegments(300);
}

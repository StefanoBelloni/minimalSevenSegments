#include "minimalSevenSegments.h"

#define A_SIZE(_a_) ( sizeof( (_a_) ) / sizeof( _a_[0] ))

static const byte digitCodeMap[] = {
  //   GFEDCBA  Segments      7-segment map:
  B00111111, // 0   "0"          AAA
  B00000110, // 1   "1"         F   B
  B01011011, // 2   "2"         F   B
  B01001111, // 3   "3"          GGG
  B01100110, // 4   "4"         E   C
  B01101101, // 5   "5"         E   C
  B01111101, // 6   "6"          DDD
  B00000111, // 7   "7"
  B01111111, // 8   "8"
  B01101111, // 9   "9"
  B01110111, // 65  'A'
  B01111100, // 66  'b'
  B00111001, // 67  'C'
  B01011110, // 68  'd'
  B01111001, // 69  'E'
  B01110001, // 70  'F'
  /* ==================================== */
  B00111101, // 71  'G'
  B01110110, // 72  'H'
  B00000110, // 73  'I'
  B00001110, // 74  'J'
  B01110110, // 75  'K'  Same as 'H'
  B00111000, // 76  'L'
  B01111111, // 77  'M'  NO DISPLAY
  B01010100, // 78  'n'
  B00111111, // 79  'O'
  B01110011, // 80  'P'
  B01100111, // 81  'q'
  B01010000, // 82  'r'
  B01101101, // 83  'S'
  B01111000, // 84  't'
  B00111110, // 85  'U'
  B00111110, // 86  'V'  Same as 'U'
  B01111111, // 87  'W'  NO DISPLAY
  B01110110, // 88  'X'  Same as 'H'
  B01101110, // 89  'y'
  B01011011  // 90  'Z'  Same as '2'
};

    void SingleSevenSegment::clean()
    {
      for (byte i = 0; i < A_SIZE(_pins); ++i) {
        digitalWrite( _pins[i], _off );
      }
    }


    void SingleSevenSegment::begin(
      byte pins[],
      byte on = HIGH,
      byte off = LOW
    )
    {
      for (byte i = 0; i < A_SIZE(_pins); ++i) {
        _pins[i] = pins[i];
        pinMode(pins[i], OUTPUT);
      }
      _on  = on;
      _off = off;
      clean();
    }

    void SingleSevenSegment::setSymbol(char c) {
      if ( c == ' ' ) {
        clean();
        return;
      }

      if ( c >= 'a' ) {
        c -= ('a' - 'A');
      }

      if ( c >= 'A' && c <= 'Z') {
        setSymbol( (byte)(c - 'A' + _alpha_offset) );
        return;
      }

      clean();
    }

    void SingleSevenSegment::setSymbol(byte n)
    {

      if ( n > A_SIZE( digitCodeMap ) ) { return; }
      byte bn = digitCodeMap[n];
      for ( byte i = 0; i < A_SIZE(_pins); ++i ) {
        digitalWrite( _pins[i], getVoltage(bn, i) );
      }

    }

    void SingleSevenSegment::setSymbol(int n) {
      setSymbol( (byte)n );
    }


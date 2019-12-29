
// #define DEBUG_ARDUINO 1

#if DEBUG_ARDUINO
  #define DEBUG_INIT() Serial.begin(9600)
  #define DEBUG(_val_) Serial.print((_val_))
  #define DEBUGLN(_val_) Serial.println((_val_))
#else
  #define DEBUG_INIT()
  #define DEBUG(_val_)
  #define DEBUGLN(_val_)
#endif

#define NUMBER_SEGMENTS 8
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

class SingleSevenSegment {

    byte _pins[NUMBER_SEGMENTS];
    byte _on;
    byte _off;
    const byte _alpha_offset = 10;

    inline byte getVoltage(byte bn, byte i)
    {
      return (bn & (1 << i) ? _on : _off);
    }

    void clean()
    {
      for (byte i = 0; i < A_SIZE(_pins); ++i) {
        digitalWrite( _pins[i], _off );
      }
    }


  public:
    SingleSevenSegment() {}

    void begin(
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

    void setSymbol(char c) {
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

    void setSymbol(byte n)
    {

      if ( n > A_SIZE( digitCodeMap ) ) { return; }
      DEBUG("Number To display: "); DEBUGLN(n);
      byte bn = digitCodeMap[n];
      for ( byte i = 0; i < A_SIZE(_pins); ++i ) {
        digitalWrite( _pins[i], getVoltage(bn, i) );
      }

    }

    void setSymbol(int n) {
      setSymbol( (byte)n );
    }

};

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

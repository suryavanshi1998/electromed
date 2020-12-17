
#include <Arduino.h>

class MCP3421
{
public:
  unsigned char tics;
  // methods
  MCP3421();
  double getDouble();
  long getLong();
  int init(int address, byte sr, byte pga);
  int getState();
  int ready();
private:

int  _adr;  // i2c address
byte _sr;  // sample rate 0..7 / 12,14,16,18 bit
byte _pga; // PGA gain 1=1, 2;=2, 3=4 , 4=8
byte _confWrite; //
byte _confRead; //
byte _b2,_b3,_b4;
long _l1;
double _db1;



};


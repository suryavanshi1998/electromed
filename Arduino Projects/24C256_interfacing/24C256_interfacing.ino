#include <Wire.h>
#include <MCP342x.h>
//Address of 24LC256 eeprom chip
uint8_t address = 0x68;
MCP342x adc = MCP342x(address);

// Configuration settings
MCP342x::Config config(MCP342x::channel1, MCP342x::oneShot,
                       MCP342x::resolution18, MCP342x::gain1);

// Configuration/status read back from the ADC
MCP342x::Config status;

// Inidicate if a new conversion should be started
bool startConversion = false;



int rtdValues[180] = {
  220, 10, 4,
  200, 18, 53,
  190, 22, 78,
  180, 27, 05,
  170, 31, 28,
  160, 35, 48,
  150, 39, 65,
  140, 43, 8,
  130, 47, 93,
  120, 52, 04,
  110, 56, 13,
  100, 60, 2,
  90, 64, 25,
  80, 68, 28,
  70, 72, 29,
  60, 76, 28,
  50, 80, 25,
  40, 84, 21,
  30, 88, 17,
  20, 92, 13,
  10, 96, 07,
  0, 100, 0,
  10, 103, 9,
  20, 107, 79,
  30, 111, 67,
  40, 115, 54,
  50, 119, 4,
  60, 123, 24,
  70, 127, 07,
  80, 130, 89,
  90, 134, 7,
  100, 138, 5,
  110, 142, 28,
  120, 146, 06,
  130, 149, 82,
  140, 153, 57,
  150, 157, 32,
  160, 161, 04,
  170, 164, 76,
  180, 168, 47,
  190, 172, 16,
  200, 175, 84,
  210, 179, 51,
  220, 183, 17,
  230, 186, 82,
  240, 190, 46,
  250, 194, 8,
  26, 197, 7,
  27, 201, 3,
  28, 204, 88,
  29, 208, 46,
  30, 212, 03,
  310, 215, 58,
  320, 219, 13,
  330, 222, 66,
  340, 226, 18,
  350, 229, 69,
  360, 233, 19,
  370, 236, 67
};



void setup(void)
{
  Serial.begin(9600);
  Wire.begin();
  MCP342x::generalCallReset();
  Wire.requestFrom(address, (uint8_t)1);
  if (!Wire.available()) {
    Serial.print("No device found at address ");
    Serial.println(address, HEX);
  }
  startConversion = true;
  /*
    for ( int i = 3; i <= 180; i++ ) {

      writeEEPROM(i, rtdValues[i]);
    }


    Serial.println("Reading Data");
    for ( int i = 0 ; i =< 180; i = i + 3) {

      readEEPROM(i);
    }*/
}

void loop() {

  calculateFour_twenty();
  delay(1500);
}



void writeEEPROM(int eeaddress, float data )
{
  const int deviceaddress =  0x50;
  int INT = data;

  int i = eeaddress;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(i >> 8));   // MSB
  Wire.write((int)(i & 0xFF)); // LSB
  Serial.print("INT :");
  Serial.println(INT);
  Wire.write(INT);
  Wire.endTransmission();

  delay(5);
}

float readEEPROM(int eeaddress )
{

  const int deviceaddress =  0x50;
  int whole = 0;
  float rtdX = 0;
  int rtdY = 0;
  int fr = 0;

  /*int fr_1 = 0;
    int rtdY_1 = 0;
    int whole_1 = 0;
  */
  // Serial.print("Addr ");
  //Serial.println(eeaddress);

  // if (eeaddress <= 119) {*/
  Wire.beginTransmission(deviceaddress);
  Wire.requestFrom(deviceaddress, 1);
  int n = eeaddress + 2;
  Serial.print("ADDR :");
  Serial.println(n);
  Wire.write((int)(n >> 8));   // MSB
  Wire.write((int)(n & 0xFF)); // LSB

  if (Wire.available()) fr = Wire.read();
  Serial.print("fr :");
  Serial.println(fr);
  Wire.endTransmission();



  Wire.requestFrom(deviceaddress, 1);
  Wire.beginTransmission(deviceaddress);
  int j = eeaddress;
  Serial.print("ADDR :");
  Serial.println(j);
  Wire.write((int)(j >> 8));   // MSB
  Wire.write((int)(j & 0xFF)); // LSB

  if (Wire.available()) rtdY = Wire.read();
  //Serial.print("addrK :");
  //Serial.println(j);
  Serial.print("RTD Y :");
  Serial.println(rtdY);
  Wire.endTransmission();

  Wire.requestFrom(deviceaddress, 1);
  Wire.beginTransmission(deviceaddress);
  int k = eeaddress + 2;
  Serial.print("ADDR :");
  Serial.println(k);
  Wire.write((int)(k >> 8));   // MSB
  Wire.write((int)(k & 0xFF)); // LSB

  if (Wire.available()) whole = Wire.read();
  // Serial.print("addrK :");
  // Serial.println(k);

  // Serial.print("Whole :");
  // Serial.println(whole);
  Wire.endTransmission();


  rtdX = ((fr * 0.01) + whole);
  Serial.print("RTD X :");
  Serial.println(rtdX);

  return rtdX, rtdY;
}



double calculateY( float X, float X1, float Y1, float X2, float Y2) {

  double Y = 0;
  Y = ((((Y2 - Y1) / (X2 - X1)) * (X - X1)) + Y1);
  Serial.print("Y :");
  Serial.println(Y);
  return Y;
}


void calculateFour_twenty() {
  long LV = 25600; //x1
  long HV = 127999; //x2
  double LR = 0; // y1
  double HR = 99999; //y2
  double ans = 0; //y
  long value = 0; //x
  // float R = 104;
  uint8_t err;


  if (startConversion) {
    Serial.println("Convert");
    err = adc.convert(config);
    if (err) {
      Serial.print("Convert error: ");
      Serial.println(err);
    }
    startConversion = false;
  }

  err = adc.read(value, status);

  if (!err && status.isReady()) {
    // For debugging purposes print the return value.
    Serial.print("Value: ");
    Serial.println(value);

    calculateY(value, LV, LR, HV, HR);


    /* ans = ((((value - LV) / (HV - LV)) * (HR - LR)) + LR);
      Serial.print("ANS :");
      Serial.println(ans);
    */
    startConversion = true;
  }
  milivolts(value);
  return value;
}


float milivolts(long bytedata) {


  float  mv =  bytedata *  1e-3 / (1 << 3 * 2  ) ; // = 1mv * ADC * / sample rate factor
  mv = ((mv / (1 << 1)) * 2) * 1000;       // divide by pga amplificati
  //return(mv);
  Serial.print("mV :");
  Serial.println(mv);


}

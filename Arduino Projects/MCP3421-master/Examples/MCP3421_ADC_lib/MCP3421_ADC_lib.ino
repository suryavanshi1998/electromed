
/* MCP3421  18-Bit Analog-to-Digital Converter with I2C Interface and On-Board Reference
   Lab3 3/2012 Nawrath
   Kunsthochschule fuer Medien Koeln
   Academy of Media Arts Cologne
   http://interface.khm.de

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  mcp adress = 0x68

  sr= Sample Rate Selection
  sr=0  ; 00 = 240 SPS (12 bits),
  sr=1  ; 01 = 60 SPS (14 bits),
  sr=2  ; 10 = 15 SPS (16 bits),
  sr=3  ; 11 = 3.75 SPS (18 bits)

  pga=  PGA Gain Selector
  0 = 1 V/V,
  1 = 2 V/V,
  2 = 4 V/V,

  MCP.init(address,sr,pga);

*/



#include <Wire.h>
#include "MCP3421.h"
MCP3421 MCP = MCP3421();



int pinVCC = 17; // pin A3 used as + Powersupply for ADC
int pinGND = 16; // pin A2 used as GND Powersupply for ADC
int pinLed = 13;

char st1[20];

long l1;
double vin;
float CV;
int ans;
int LV = 0.4;
int HV = 2;
int LR = 0;
int HR = 9999;


void setup(void)
{
  Serial.begin(115200);

  pinMode(pinVCC, OUTPUT);
  pinMode(pinGND, OUTPUT);
  pinMode(pinLed, OUTPUT);

  digitalWrite(pinVCC, 1); // switch on pin for MCP3421 5 volt powersupply

  Serial.println("ADC MCP 3421");  // just to be sure things are working
  Wire.begin();
  delay(1000);
  Serial.println("begin");

  MCP.init(0x68, 1,3);


}

void loop(void)
{


  //while (MCP.ready() == 0);
  //MCP.getLong();

  digitalWrite(pinLed, 1);

  l1 = MCP.getLong();
  Serial.print("  ");
  sprintf(st1, "ld %ld", l1);
  /*Serial.print(st1);
  Serial.print("\n");
  vin = MCP.getDouble();
  CV = vin;
  if (vin >= 0.4 && vin <= 2.0) {
    ans = (((CV-LV)/(HV-LV)*(HR-LR))+LR);
    Serial.println("\n");
    Serial.println("ANS :");
    Serial.print(ans);
    Serial.print("\n");
  }
  
  /*Serial.print(" V:");
  Serial.print(CV);

  Serial.print("  mV:");
  Serial.print(CV * 1000);
  Serial.print("  ");

  vin = vin * 1000;
  Serial.print("  mV:");
  sprintDouble(st1, vin, 3);
  Serial.print(st1);

  Serial.println("  ");*/
  digitalWrite(pinLed, 0);
  delay(2000);


}




//******************************************************************************************
void sprintDouble( char *str, double val, byte precision) {
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimial places
  // example: lcdPrintDouble( 3.1415, 2); // prints 3.14 (two decimal places)
  char st2[16];
  unsigned long frac;
  unsigned long mult = 1;
  int mant = int(val);
  byte padding = precision - 1;
  byte sgn = 0;

  sprintf(str, "");
  if (val < 0)  sprintf(str, "-");
  mant = abs(mant);
  sprintf(st2, "%d", mant); //prints the int part
  strcat(str, st2);

  if ( precision > 0) {
    strcat(str, ".");

    while (precision--)
      mult *= 10;

    if (val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val) - val ) * mult;
    unsigned long frac1 = frac;
    int cnt = precision;
    // while( frac1 /= 10 )
    while ( frac1 = frac1 / 10 & cnt--  )
      padding--;
    while (  padding--)  strcat(str, "0");
    sprintf(st2, "%ld", frac);



    strcat(str, st2);



  }

}

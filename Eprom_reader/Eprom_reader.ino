
#include <EEPROM.h>
 
// the current address in the EEPROM (i.e. which byte
// we're going to read from)
int addr = 1;
 
void setup()
{
  EEPROM.begin(512);  //Initialize EEPROM
  Serial.begin(115200); //Serial communication to display data
  // read appropriate byte of the EEPROM.  
  Serial.println(""); //Goto next line, as ESP sends some garbage when you reset it  

  for (int addr=0;addr<250;addr++)
  {
  Serial.print(char(EEPROM.read(addr)));    //Read from address 0x00
  }
} 

 
void loop()
{
  //We dont have anything in loop as EEPROM reading is done only once
  delay(10);   
}

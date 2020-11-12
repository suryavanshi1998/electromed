
#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to read from)
int addr = 0;

void setup()
{
  EEPROM.begin(512);  //Initialize EEPROM
  Serial.begin(115200); //Serial communication to display data
  // read appropriate byte of the EEPROM.
  Serial.println(""); //Goto next line, as ESP sends some garbage when you reset it
  Serial.print("\nssid :");
  for (int addr = 0; addr < 20; addr++)
  {
    const char ssid (EEPROM.read(addr));    //Read from address 0x00
    

    Serial.print(ssid);

  }
  Serial.print("\nPassword :");
  for (int addr = 100; addr < 120; addr++)
  {
     char str[20]= { (EEPROM.read(addr)) };   //Read from address 0x00

    Serial.print(str);


  }
  Serial.print("\nIP addresss :");
  for (int addr = 200; addr < 216; addr++)
  {
    const char ip (EEPROM.read(addr));    //Read from address 0x00

    Serial.print(ip);

  }

}


void loop()
{
  //We dont have anything in loop as EEPROM reading is done only once
  delay(10);
}

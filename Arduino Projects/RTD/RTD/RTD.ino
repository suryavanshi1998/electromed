/*
   EEPROM Write

   Stores values read from analog input 0 into the EEPROM.
   These values will stay in the EEPROM when the board is
   turned off and may be retrieved later by another sketch.
*/

#include <EEPROM.h>
//#include"pt100.h"

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int addr = 0;
//float x[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
void setup() {
  Serial.begin(9600);
  eprom_rtd();

}

void loop() {

  eprom_read();

  delay(1000);
}



float eprom_read() {
  byte x1;
  int i = 0;
  for (i = 1; i < 20; i++) {
    x1 =  EEPROM.read(i);
     Serial.print(x1);
  }
 // Serial.print(x1);

}





void eprom_rtd() {
  int i = 0;
  int x[10] = {10};
  for (i = 1; i < 20; i++) {
    EEPROM.write(i, x);
  }

}

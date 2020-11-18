#include <EEPROM.h>

int reset_mode = 13;
int ledpin = 12;

int addr = 1;

void setup()
{

  pinMode(ledpin, OUTPUT);
  pinMode(reset_mode, INPUT);
  Serial.begin(115200);
  EEPROM.begin(512);  //Initialize EEPROM

  // write to EEPROM.
  /* EEPROM.write(addr, '0');
    addr++;                      //Increment address
    EEPROM.write(addr, '1');
    addr++;                      //Increment address
    //EEPROM.write(addr, 'C');

    //Write string to eeprom
    /*String sample = "testing eeprom";
     for(int i=0;i<sample.length();i++)
     {
     EEPROM.write(0x0F+i, sample[i]); //Write one by one with starting address of 0x0F
     }*/
  delay(5000);
  int temp = digitalRead(reset_mode);
  if (temp == 1) {
    EEPROM.write(addr, '1');
    delay(100);
    digitalWrite(ledpin, HIGH);
    Serial.println("\n SETIING TO NORMAL MODE");


  }
  delay(5000);
  BootMode();

  EEPROM.commit();
  //Store data to EEPROM


}

void BootMode() {
  char boot_mode = '1';
  boot_mode = (EEPROM.read(addr));  //Read from address 0x00
  delay(100);
  Serial.print("Test :");
  Serial.print(boot_mode);


  if (boot_mode == '0') {
    Serial.println("\nBoot in Reset Mode");
  }

  else {


    Serial.println("\nBoot in Normal Mode");
  }

}

void ResetMode() {
  int temp = digitalRead(reset_mode);
  if (temp == 1) {
    EEPROM.write(addr, '0');
    delay(100);
    digitalWrite(ledpin, HIGH);
    Serial.println("\n Reset Mode ON");
    //delay(1000);

  }
  else {

  }
}



void loop()
{

  ResetMode();
  EEPROM.commit();
  delay(1000);
}

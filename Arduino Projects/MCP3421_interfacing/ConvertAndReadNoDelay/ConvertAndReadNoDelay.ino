#include <Wire.h>
#include <MCP342x.h>
#include <EEPROM.h>

/* Demonstrate the use of read() and convert(). If read() is called
   immediately after convert then the conversion will not have
   completed. Two approaches to avoid this problem are possible, use
   delay() or similar to wait a fixed amount of time, or to
   periodically read the device and check the config result.
*/


// 0x68 is the default address for all MCP342x devices
uint8_t address = 0x68;
MCP342x adc = MCP342x(address);

// Configuration settings
MCP342x::Config config(MCP342x::channel1, MCP342x::oneShot,
                       MCP342x::resolution18, MCP342x::gain1);

// Configuration/status read back from the ADC
MCP342x::Config status;

// Inidicate if a new conversion should be started
bool startConversion = false;


// LED details
#ifdef LED_BUILTIN
int led = LED_BUILTIN;
#else
int led = 13;
#endif
bool ledLevel = false;
int mode_0 = 2;

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();

  // Enable power for MCP342x (needed for FL100 shield only)
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

  pinMode(led, OUTPUT);
  pinMode(mode_0, INPUT);
  eprom();
  boot_mode();
  // Reset devices
  MCP342x::generalCallReset();
  delay(1); // MC342x needs 300us to settle

  // Check device present
  Wire.requestFrom(address, (uint8_t)1);
  if (!Wire.available()) {
    Serial.print("No device found at address ");
    Serial.println(address, HEX);
    while (1)
      ;
  }

  // First time loop() is called start a conversion
  startConversion = true;
}

unsigned long lastLedFlash = 0;
void loop(void)
{

  mode0();
  // Do other stuff here, such as flash an LED
  /* if (millis() - lastLedFlash > 50) {
     ledLevel = !ledLevel;
     digitalWrite(led, ledLevel);
     lastLedFlash = millis();
    }*/
  delay(2000);

}


void mode0() {
  mode_0 = HIGH;

  double LV = 25600;
  double HV = 127999;
  double LR = 0;
  double HR = 99999;
  double ans = 0;

  if (mode_0 == HIGH) {

    long value = 0;
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
      ans = ((((value - LV) / (HV - LV)) * (HR - LR)) + LR);
      Serial.print("ANS :");
      Serial.println(ans);
      //Serial.print("Config: 0x");
      // Serial.println((int)config, HEX);
      // Serial.print("Convert error: ");
      //Serial.println(err);
      startConversion = true;

 
 float  mv =  value *  1e-3 / (1 << 3*2  ) ; // = 1mv * ADC * / sample rate factor
  mv = ((mv / (1 <<1))*2)*1000;            // divide by pga amplificati
  //return(mv);
  Serial.println(mv);

    }

  }
}

void eprom() {
  mode_0 = HIGH;
  int val = 0;
  if (mode_0 == HIGH) {

    int addr = 0;
    val = 1;
    EEPROM.write(addr, val);

    addr = addr + 1;
    if (addr == EEPROM.length()) {
      addr = 0;
      delay(100);

    }
  }
}


void boot_mode() {
  int address = 0;
  byte value;
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();

  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }
}

#include <Wire.h>
#include <MCP342x.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(0, 1, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN

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


void setup(void)
{
  // Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  // Enable power for MCP342x (needed for FL100 shield only)
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





void loop()
{
  mV();
  delay(1000);

}


void mV() {

  double LV = 25600;
  double HV = 127999;
  double LR = 0;
  double HR = 99999;
  double ans = 0;
  long value = 0;
  uint8_t err;

  if (startConversion) {
    //Serial.println("Convert");
    err = adc.convert(config);
    if (err) {
      //Serial.print("Convert error: ");
      //Serial.println(err);
    }
    startConversion = false;
  }

  err = adc.read(value, status);
  if (!err && status.isReady()) {
    // For debugging purposes print the return value.
    //Serial.print("Value: ");
    //Serial.println(value);
    ans = ((((value - LV) / (HV - LV)) * (HR - LR)) + LR);
    // Serial.print("ANS :");
    //Serial.println(ans);
    //Serial.print("Config: 0x");
    //Serial.println((int)config, HEX);
    startConversion = true;


    float  mv =  value *  1e-3 / (1 << 3 * 2  ) ; // = 1mv * ADC * / sample rate factor
    mv = ((mv / (1 << 1)) * 2) * 1000;       // divide by pga amplification
    //  Serial.print("mV");
    //Serial.println(mv);

    lcd.print("mV :");//print name
    lcd.setCursor(4, 0);// set the cursor to column 0, line1
    lcd.print(mv);//print name

    lcd.setCursor(0, 1); // set the cursor to column 0, line 2

    lcd.print("Ans:");//print name
    lcd.setCursor(4, 1);

    lcd.print(ans);//print name
    delay(750);//delay of 0.75sec
    lcd.setCursor(0, 0);// set the cursor to column 0, line1

  }
}

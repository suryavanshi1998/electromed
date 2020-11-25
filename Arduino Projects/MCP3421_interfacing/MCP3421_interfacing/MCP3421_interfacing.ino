// Include libraries this sketch will use
#include  <Wire.h>
#include  <MCP342x.h>
 
// Instantiate objects used in this project
MCP342x myADC;
int outputPin = 6;
 
void setup() 
{
  Wire.begin();  // join I2C bus
  TWBR = 12;  // 400 kHz (maximum)
 
  Serial.begin(9600); // Open serial connection to send info to the host
  while (!Serial) {}  // wait for Serial comms to become ready
  Serial.println("Starting up");
  Serial.println("Testing device connection...");
  Serial.println(myADC.testConnection() ? "MCP342x connection successful" : "MCP342x connection failed");
 
  myADC.configure( MCP342X_MODE_CONTINUOUS |
                   MCP342X_CHANNEL_1 |
                   MCP342X_SIZE_16BIT |
                   MCP342X_GAIN_1X
                 );
 
  Serial.println(myADC.getConfigRegShdw(), HEX);
 
}  // End of setup()
 
void loop() {
  static int16_t  result;
  for(int i=0; i<=255; i++)
  {
    myADC.startConversion();
    analogWrite(outputPin, i);
    myADC.getResult(&result);
    Serial.print(i);
    Serial.print("  ");
    Serial.print(result);
    Serial.print("  ");
    Serial.println(result, HEX);
  }
 
}  // End of loop()

union MyUnion {
  float f;
  byte b[4];
};

void setup()
{
  Serial.begin(9600);
  MyUnion myData;
  myData.f = 3.14159265359;  // I only ever assign a value to the float!
  Serial.println(myData.f);
  for (int i = 0; i < 4; i++)
  {
    //printAllByte(myData.b[3 - i]); // but each element of the byte array has a value
    Serial.println(myData.b[i], BIN);
  }
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:

}
void printAllByte(byte theByte)
{
  for (byte i = 0; i < 8; i++)
  {
    Serial.print(bitRead(theByte, 7 - i) ? "1" : "0");
  }
}

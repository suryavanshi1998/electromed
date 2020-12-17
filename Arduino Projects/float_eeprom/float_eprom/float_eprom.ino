
#include <EEPROM.h>
double temp;
float rtdValues[] = {
  -220, 10.4,
  -200, 18.53,
  -190, 22.78,
  -180, 27.05,
  -170, 31.28,
  -160, 35.48,
  -150, 39.65,
  -140, 43.8,
  -130, 47.93,
  -120, 52.04,
  -110, 56.13,
  -100, 60.2,
  -90, 64.25,
  -80, 68.28,
  -70, 72.29,
  -60, 76.28,
  -50, 80.25,
  -40, 84.21,
  -30, 88.17,
  -20, 92.13,
  -10, 96.07,
  0, 100,
  10, 103.9,
  20, 107.79,
  30, 111.67,
  40, 115.54,
  50, 119.4,
  60, 123.24,
  70, 127.07,
  80, 130.89,
  90, 134.7,
  100, 138.5,
  110, 142.28,
  120, 146.06,
  130, 149.82,
  140, 153.57,
  150, 157.32,
  160, 161.04,
  170, 164.76,
  180, 168.47,
  190, 172.16,
  200, 175.84,
  210, 179.51,
  220, 183.17,
  230, 186.82,
  240, 190.46,
  250, 194.08,
  260, 197.7,
  270, 201.3,
  280, 204.88,
  290, 208.46,
  300, 212.03,
  310, 215.58,
  320, 219.13,
  330, 222.66,
  340, 226.18,
  350, 229.69,
  360, 233.19,
  370, 236.67
};


struct MyObject2 {
  float x;
};

float R = 104.24;
void setup() {
  Serial.begin(9600);
  eeprom_put();
  delay(1000);
  Serial.println("Reading Memory");
  secondTest();
}


void eeprom_put() {
  while (!Serial) {
  }
  int eeAddress = 0;   //Location we want the data to be put.

  Serial.println("Written float data type!");

  for ( int i = 0; i < 44; i += 2 ) {
    int diff = (int)rtdValues[i + 3] - (int)rtdValues[i + 1];
    for (int j = 0; j < diff; j++) {
      int addr = ((int)rtdValues[i + 1] + j) * 10;
      EEPROM.put(addr, rtdValues[i]);
      EEPROM.put(addr + 4, rtdValues[i + 1]);
      Serial.print("ADDRESS : ");
      Serial.print(addr);
      Serial.print(",  x : ");
      Serial.print(rtdValues[i + 1]);
      Serial.print(",  Y :");
      Serial.println(rtdValues[i]);
    }
  }


}


void secondTest() {
  int i = 0;

  MyObject2 customVar; //Variable to store custom object read from EEPROM.
  for (i = 10; i <= 100 ; i++) {
    int addr = i * 10;
    EEPROM.get(addr, customVar);
    float X = customVar.x;
    EEPROM.get(addr + 4, customVar);
    float Y = customVar.x;
    Serial.print("Address : ");
    Serial.print(addr);
    Serial.print(",  X :");
    Serial.print(X);
    Serial.print(",  Y :");
    Serial.println(Y);
  }
}


void loop() {

  // delay(5000);
}

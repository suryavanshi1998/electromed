#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#define trigger 14
#define LED 12
#define power 3
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(trigger,INPUT); 
    pinMode(LED,OUTPUT); 
     pinMode(power,OUTPUT);    
    if(digitalRead(trigger) == HIGH){
    digitalWrite(power,HIGH);
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("Electro-Med WiFi Manager");
    Serial.println("connected :)");
  }     
}
void loop() { 
  if (WiFi.status() == WL_CONNECTED)
        {
          digitalWrite(power,LOW);
          while(WiFi.status() == WL_CONNECTED){           
            digitalWrite(LED,HIGH);
            delay(500);
            digitalWrite(LED,LOW);
            delay(200);   
          }              
        }
        else {
          digitalWrite(LED,LOW);
        }
}

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#define trigger 13

#define LED 12
#define power 14

ESP8266WebServer server(80);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigger, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(power, OUTPUT);
  
}

void loop() {


  if (digitalRead(trigger) == HIGH) {
    digitalWrite(power, HIGH);
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("Electro-Med WiFi Manager");
    Serial.println("connected :)");

    if (WiFi.status() == WL_CONNECTED)
    {
      digitalWrite(LED, HIGH);
      
    }
    else {
      digitalWrite(LED, LOW);
    }
  }
}

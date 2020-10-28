#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
const char* ssid = "emed@17vnpuri"; // You Wifi Name
const char* password = "D17vnpuri"; // Wifi Password
 
const IPAddress remote_ip(192,168,1,24); // Remote host
 
void setup() {
Serial.begin(115200);
delay(10);
 
// We start by connecting to a WiFi network
 
Serial.println();
Serial.println("Connecting to WiFi");
 
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
delay(100);
Serial.print(".");
}
 
Serial.println();
Serial.print("WiFi connected with ip ");
Serial.println(WiFi.localIP());
 
Serial.print("Pinging ip ");
Serial.println(remote_ip);
 
// Ping
if (Ping.ping(remote_ip)) {
Serial.println("Success!!");
} else {
Serial.println("Error :(");
}
}
 
void loop() {
// loop
}


// Libraries
#include <ESP8266WiFi.h>
#include "emedwifi2.h"

//const char* ssid     = "emed@17vnpuri";
//const char* password = "D17vnpuri";// Host
const char* host = "65.0.21.230";

int buttonPin = 5;
void setup() {

  // Serial
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClient class to create TCP connections

}

void loop() {

  //DeviceON();
  String input = "";
  String url = "";
  // Use WiFiClient class to create TCP connections


  int  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // turn LED on:
    url = "http://65.0.21.230/writeDevice1.php?Value=1";
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    // turn LED off:

    url = "http://65.0.21.230/writeDevice1.php?Value=0";
    digitalWrite(LED_BUILTIN, HIGH);
  }

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");

  }
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.print("connecting to ");
  Serial.println(host);
  delay(100);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  // Read all the lines from the answer

  unsigned long timeout = millis();

  while (client.available() == 0) {
    yield();
    if (millis() - timeout > 10000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
    }
  }


  while (client.available()) {
    input += client.readStringUntil('\r');
    //input = input.substring(input.indexOf('{'));
  }



  //Serial.println("Device");
  Serial.println(input);
 // yield();
 delay(100);
}

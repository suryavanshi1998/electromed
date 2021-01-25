
// Libraries
#include <ESP8266WiFi.h>
#include "emedwifi1.h"
#include <ArduinoJson.h>

// SSID
//const char* ssid     = "emed@17vnpuri";
//const char* password = "D17vnpuri";// Host
const char* host = "65.0.21.230";


// Current time


// Previous time
//unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
//const long timeoutTime = 10000;
//int field1 = 0;
int Device1 = 14;
int Device2 = 12;
int Device3 = 13;
String data = "";
void setup() {
  // Serial

  Serial.begin(115200);
  delay(10);
  pinMode(Device1, OUTPUT);
  pinMode(Device2, OUTPUT);
  pinMode(Device3, OUTPUT);
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
}

void loop() {

  //device();
  parseDevice1();
  //delay(500);
  parseDevice2();
  //delay(500);
  parseDevice3();
  //delay(500);
}





String device() {


  String input = "";
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "connection failed";
  }


  // We now create a URI for the request
  String url = "http://65.0.21.230/read.php";


  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.print("connecting to ");
  Serial.println(host);


  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  // Read all the lines from the answer

  unsigned long timeout = millis();

  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return "timeout";
    }
  }


  while (client.available()) {
    input += client.readStringUntil('\r');
    input = input.substring(input.indexOf('{'));
  }



  Serial.println("Device");
  Serial.println(input);


  return input;


}

int parseDevice1() {

  data = device();
  //Serial.println(data);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(data);
  delay(10);


  int Device1_data = root["feeds"][0]["Device1"];
  Device1_data = root["feeds"][0]["Device1"].as<int>();
  root["feeds"][0]["Device1"] = Device1_data;
  // Serial.print("ID");
  Serial.println(Device1_data);


  if (Device1_data == 1) {

    digitalWrite(Device1, HIGH);
    Serial.println("ON");
  }

  else {
    digitalWrite(Device1, LOW);
  }

  jsonBuffer.clear();

}


int parseDevice2() {

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(data);
  delay(10);

  int Device2_data = root["feeds"][1]["Device2"];
  Device2_data = root["feeds"][1]["Device2"].as<int>();
  root["feeds"][1]["Device2"] = Device2_data;
  // Serial.print("ID");
  Serial.println(Device2_data);



  if (Device2_data == 1) {

    digitalWrite(Device2, HIGH);
    Serial.println("ON");
  }

  else {
    digitalWrite(Device2, LOW);
  }

  jsonBuffer.clear();
}


int parseDevice3() {

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(data);
  delay(10);
  int Device3_data = root["feeds"][2]["Device3"];
  Device3_data = root["feeds"][2]["Device3"].as<int>();
  root["feeds"][2]["Device3"] = Device3_data;
  // Serial.print("ID");
  Serial.println(Device3_data);

  if (Device3_data == 1) {

    digitalWrite(Device3, HIGH);
    Serial.println("ON");
  }

  else {
    digitalWrite(Device3, LOW);
  }

  jsonBuffer.clear();
}

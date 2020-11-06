
// Libraries
#include <ESP8266WiFi.h>
#include "emedwifi.h"
#include <ArduinoJson.h>
// SSID
//const char* ssid     = "emed@17vnpuri";
//const char* password = "D17vnpuri";// Host
const char* host = "35.154.55.24";


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


void setup() {

  // Serial

  Serial.begin(115200);
  delay(10);

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

  // delay(3600000);
  DynamicJsonBuffer jsonBuffer;
  Serial.print("connecting to ");
  Serial.println(host);


  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "http://api.airpollutionapi.com/1.0/aqi?lat=26.8718431&lon=80.9459051&APPID=qsfmma0bkgr296g79ogrhfubg5";

  // Send request
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();

  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines from the answer
  while (client.available()) {
    String  input = client.readStringUntil('\r');
    Serial.print(input);
    JsonObject& root = jsonBuffer.parseObject(input);

    String status = root["status"];
    status = root["status"].as<String>();
    root["status"] = status;

    String temp = root["data"]["temp"];
    temp = root["data"]["temp"].as<String>();
    root["data"]["temp"] = temp;

    String Humidity  = root["data"]["aqiParams"][5]["value"];
    Humidity = root["data"]["aqiParams"][5]["value"].as<String>();
    root["data"]["aqiParams"][5]["value"] = Humidity;

    String wind_speed  = root["data"]["aqiParams"][7]["value"];
    wind_speed = root["data"]["aqiParams"][7]["value"].as<String>();
    root["data"]["aqiParams"][7]["value"] = wind_speed;


    String wind_direction  = root["data"]["aqiParams"][8]["value"];
    wind_direction = root["data"]["aqiParams"][8]["value"].as<String>();
    root["data"]["aqiParams"][8]["value"] = wind_direction;

    /*String alert = root["data"][0]["alert"];

      String Name2 = root["data"][0]["aqiParams"][1]["name"];




      alert = root["data"][0]["alert"].as<String>();
      Name2 = root["data"][0]["aqiParams"][1]["name"].as<String>();



      root["data"][0]["alert"] = alert;

      root["data"][0]["aqiParams"][1]["name"] = Name2;

      //Serial.print("\n");
      //Serial.print("Status -->>:");
      Serial.print(status);
      /*Serial.print("\n");
      Serial.print("Temp:");
      Serial.print(temp);
      Serial.print("\n");*/


    String output;
    //root.printTo(output);
    // Serial.print(output);

    // root.printTo(wind_speed);
    // Serial.print("STATUS :");
    Serial.print(status);
    Serial.print("\n");
    //Serial.print("Polution Status :");
    Serial.print(temp);
    Serial.print("\n");
    // Serial.print("NAME :");
    Serial.print(Humidity);
    Serial.print("\n");
    Serial.print(wind_speed);

    Serial.print("\n");
    Serial.print(wind_direction);
    /* Serial.print(Name2);
      Serial.print("\n");
      Serial.print(alert);*/

  }
  delay(360000);

  // Close connecting
  Serial.println();
  Serial.println("closing connection");
}

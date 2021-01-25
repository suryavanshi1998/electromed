#include <ESP8266WiFi.h>
#include "emedwifi.h"
#include <ArduinoJson.h>
/*
  String input = "";
  //String Temp = "";
  //String Humidity = "";
  //String wind_speed = "";
  //String wind_direction = "";
  //String status = "";
*/
String api_request () {


  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0;
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  const long timeoutTime = 2000;

  const char* host = "35.154.55.24";

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "connection failed";
  }


  String url = "http://api.airpollutionapi.com/1.0/aqi?lat=26.8718431&lon=80.9459051&APPID=qsfmma0bkgr296g79ogrhfubg5";

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
      return "Client Timeout";
    }
  }
  delay(400);
  String input2 = "";
  while (client.available()) {
    input2 += client.readStringUntil('\r');
    Serial.print(input2);
  }
  //Serial.println("TEST");
  input2 = input2.substring(input2.indexOf('{'));
  //Serial.print(input2);
  return input2;

}




void wifi_setup()
{
  /* const char* ssid     = "emed@17vnpuri";
    const char* password = "D17vnpuri";// Host
    IPAddress local_IP(192, 168, 1, 184);
    // Set your Gateway IP address
    IPAddress gateway(192, 168, 1, 1);

    IPAddress subnet(255, 255, 0, 0);
    IPAddress primaryDNS(8, 8, 8, 8);   //optional
    IPAddress secondaryDNS(8, 8, 4, 4); //optional
  */

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");

  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  return;

}


void json_parse (String input2) {
  // void apirequest ();
 // Serial.println(input2);
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(input2);



  String status = root["status"];
  status = root["status"].as<String>();
  root["status"] = status;

  String temp = root["data"]["temp"];
  temp = root["data"]["temp"].as<String>();
  root["data"]["temp"] = temp;

  String Humidity  = root["data"]["aqiParams"][5]["value"];
  Humidity = root["data"]["aqiParams"][5]["value"].as<String>();
  root["data"]["aqiParams"][5]["value"] = Humidity;

  String wind_speed  = root["data"]["aqiParams"][6]["value"];
  wind_speed = root["data"]["aqiParams"][6]["value"].as<String>();
  root["data"]["aqiParams"][6]["value"] = wind_speed;


  String wind_direction  = root["data"]["aqiParams"][7]["value"];
  wind_direction = root["data"]["aqiParams"][7]["value"].as<String>();
  root["data"]["aqiParams"][7]["value"] = wind_direction;

  String output;
  Serial.print("status-->");
  Serial.print(status);
  Serial.print("\n");
  Serial.print("Temp-->");
  Serial.print(temp);
  Serial.print("\n");
  Serial.print("humidity-->");
  Serial.print(Humidity);
  Serial.print("\n");
  Serial.print("wind speed-->");
  Serial.print(wind_speed);
  Serial.print("\n");
  Serial.print("wind direction-->");
  Serial.print(wind_direction);

}

void setup()
{
  Serial.begin(115200);
  delay(10);
  wifi_setup();


  String returnedString = api_request ();
  //Serial.println(returnedString);
  delay(5000);


  json_parse (returnedString);
  delay(10000);
}

void loop()
{


}

/*#include <ESP8266WiFi.h>
  #include "emedwifi.h"*/
#include <ArduinoJson.h>
/*
  String input = "";
  //String Temp = "";
  //String Humidity = "";
  //String wind_speed = "";
  //String wind_direction = "";
  //String status = "";
*/

/*
  String time_api () {


  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0;
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  const long timeoutTime = 2000;

  const char* host = "api.timezonedb.com";
  // const char* host = "20.49.104.6";

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "connection failed";
  }


  //String url = "http://worldclockapi.com/api/json/est/now";
    String url = "http://api.timezonedb.com/v2.1/get-time-zone?key=OL4S2K3JTIWD&format=json&by=zone&zone=Asia/Kolkata";

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
/*
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
*/

void json_parse () {
  // void apirequest ();
  // Serial.println(input2);
  String input2 = "{\"status\":\"OK\",\"message\":\",\"countryCode\":\"IN\",\"countryName\":\"India\",\"zoneName\":\"Asia/Kolkata\",\"abbreviation\":\"IST\",\"gmtOffset\":19800,\"dst\":\"0\",\"zoneStart\":-764145000,\"zoneEnd\":null,\"nextAbbreviation\":null,\"timestamp\":1604611175,\"formatted\":\"2020-11-05 21:19:35\"}";

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(input2);



  String status = root["status"];
  status = root["status"].as<String>();
  root["status"] = status;

  String Time = root["formatted"];
  Time = root["formatted"].as<String>();
  root["data"]["formatted"] = Time;

  String output;
  Serial.print("status  :");
  Serial.print(status);
  Serial.print("\n");
  Serial.print("Date & Time  :");
  Serial.print(Time);
  Serial.print("\n");


}

void setup()
{
  Serial.begin(115200);
  delay(10);
  //  wifi_setup();


  //String returnedString = time_api ();
  //Serial.println(returnedString);
  delay(5000);

  json_parse ();
  delay(10000);
}

void loop()
{


}

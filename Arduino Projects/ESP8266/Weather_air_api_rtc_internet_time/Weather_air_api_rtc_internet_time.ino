#include <ESP8266WiFi.h>
#include "emedwifi.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "reset.h"
#define power 14
#include "Wire.h"
#include "uEEPROMLib.h"

int normal_mode = 1;
int hotspot_mode = 2;






// uEEPROMLib eeprom;
uEEPROMLib eeprom(0x57);

ESP8266WebServer server(81);
DateTime now;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int reset_mode = 13;
int ledpin = 12;

RTC_DS3231 rtc;

void setup()
{

#ifdef ARDUINO_ARCH_AVR
  int inttmp = 32123;
#else
  // too long for AVR 16 bits!
  int inttmp = 24543557;
#endif



  Wire.begin(); // D3 and D4 on ESP8266
  pinMode(power, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(reset_mode, INPUT);// declare push button as input
  EEPROM.begin(512);//Starting and setting size of the EEPROM
  Serial.begin(115200);
  delay(8000);

  server.begin();
  Serial.println("HTTP server started\n");
  delay(10);
  delay(1000);
  eprom();
  wifi_setup();


  String returnedString = aqi_weather_api ();
  //Serial.println(returnedString);
  delay(5000);


  json_parse (returnedString);
  delay(10000);

  String returned_String = time_api ();
  //Serial.println(returnedString);
  delay(1000);

  String returned_DateTime =  json_parse_time (returned_String);
  delay(1000);
  //  Serial.print("test....");
  // Serial.print(returned_DateTime);
  rtc_time(returned_DateTime);
  show();
  server.handleClient();


}


void loop()
{
  bootmode();
  int temp = digitalRead(reset_mode);


  if (temp == 1)
  {
    EEPROM.write(1, hotspot_mode);
    digitalWrite(power, HIGH);
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("Electro-Med WiFi Manager");
    Serial.println("connected :)");

    if (WiFi.status() == WL_CONNECTED)
    {
      digitalWrite(power, LOW);
      while (WiFi.status() == WL_CONNECTED) {
        digitalWrite(ledpin, HIGH);
        //Serial.println(WiFi.localIP());
        delay(1000);
        //resetMode();
        server.on("/", handleRoot);
        server.onNotFound(handleNotFound);
        delay(36000);
        return;
      }

    }

    else {
      digitalWrite(ledpin, LOW);
    }


    /**IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);**/
    //Configuring the web server
    delay(100);


  }

  else
  {
    EEPROM.write(1, normal_mode);
  }
}



void resetMode()

{
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  //server.begin();
  // Serial.println("HTTP server started");
}







void wifi_setup()
{
  delay(100);
  // IPAddress local_IP(192, 168, 1, 184);
  // Set your Gateway IP address
  /* IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 0, 0);
    IPAddress primaryDNS(8, 8, 8, 8);   //optional
    IPAddress secondaryDNS(8, 8, 4, 4); //optional*/


  unsigned int addr = 0;
  String ssid1 = "";
  String password1 = "";
  String ipaddr = "";
  String ssid2 = "";

  for ( addr = 33; addr < 128; addr++) {
    {
      ssid1 = ( ( char) eeprom.eeprom_read(addr));
    }


    Serial.print(ssid1);
  }
  Serial.println();

  delay(100);
  Serial.print("password :");
  for ( addr = 33; addr < 128; addr++) {
    {
      password1 = ( (char) eeprom.eeprom_read(addr));
    }

    Serial.print(password1);

  }
  Serial.println();

  Serial.print("IP :");
  for ( addr = 33; addr < 128; addr++) {
    {
      ipaddr = ( (char) eeprom.eeprom_read(addr));
    }
    // Serial.println();

    Serial.print(ipaddr);

  }
  Serial.println();



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



String aqi_weather_api () {


  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0;
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  const long timeoutTime = 2000;

  const char* host = "3.154.55.24";

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
  String input = "";
  while (client.available()) {
    input += client.readStringUntil('\r');
    //Serial.print(input);
  }
  //Serial.println("TEST");
  input = input.substring(input.indexOf('{'));
  Serial.print(input);
  return input;

}


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
  Serial.print("\n");
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
    //Serial.print(input2);
  }
  //Serial.println("TEST");
  input2 = input2.substring(input2.indexOf('{'));
  Serial.print(input2);
  return input2;

}





void json_parse (String input) {
  // void apirequest ();
  // Serial.println(input2);
  DynamicJsonBuffer jsonBuffer;
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



String json_parse_time (String input2) {

  DynamicJsonBuffer jsonBuffer1;
  JsonObject& root = jsonBuffer1.parseObject(input2);



  String status = root["status"];
  status = root["status"].as<String>();
  root["status"] = status;

  String date_time = root["formatted"];
  date_time = root["formatted"].as<String>();
  root["data"]["formatted"] = date_time;



  String output;
  Serial.print("status  :");
  Serial.print(status);
  Serial.print("\n");
  /* Serial.print("Date & Time  :");
    Serial.print(date_time);
    Serial.print("\n");
    /*
     Serial.print("Time :");
     Serial.print(time);
     Serial.print("\n");
     Serial.print("Date :");
     Serial.print(date);
  */
  return date_time;


}


void rtc_time(String date_time) {


  String Year = date_time.substring(1, 4);
  String Month = date_time.substring(5, 7);
  String Day = date_time.substring(9, 10);

  String Hour = date_time.substring(11, 13);
  String Minute = date_time.substring(14, 16);
  String Second = date_time.substring(17, 19);

  int Y = Year.toInt();
  int Mo = Month.toInt();
  int D = Day.toInt();

  int H = Hour.toInt();
  int M = Minute.toInt();
  int S = Second.toInt();

  /*Serial.print("test.....\n");
    Serial.print("Date  :");
    Serial.print(date);
    Serial.print("\nTime  :");
    Serial.print(time);
  */
  if (! rtc.begin())
  {
    Serial.println("Couldn't find RTC Module");
    while (1);
  }

  if (rtc.lostPower())
  {

    Serial.println("RTC lost power, lets set the time!");

    rtc.adjust(DateTime(Y, Mo, D, H, M, S));
  }

  rtc.adjust(DateTime(Y, Mo, D, H, M, S));
}


void show()
{
  now = rtc.now();
  delay(500);
  Serial.print("\n");
  Serial.print("RTC Date  :");
  Serial.print(now.day());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.year());
  Serial.print("\n");

  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print("\n");
  Serial.print("RTC TIME :");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.print("    ");
}




void handleRoot() {
  if (server.hasArg("ssid") && server.hasArg("Password") && server.hasArg("IP") && server.hasArg("GW") ) { //If all form fields contain data call handelSubmit()
    handleSubmit();
  }
  else {//Redisplay the form
    server.send(200, "text/html", INDEX_HTML);
  }
}


void handleSubmit() { //dispaly values and write to memmory
  String response = "<p>The ssid is ";
  response += server.arg("ssid");
  response += "<br>";
  response += "And the password is ";
  response += server.arg("Password");
  response += "<br>";
  response += "And the IP Address is ";
  response += server.arg("IP");
  response += "</P><BR>";
  response += "<H2><a href=\"/\">go home</a></H2><br>";

  server.send(200, "text/html", response);
  //calling function that writes data to memory
  write_to_Memory(String(server.arg("ssid")), String(server.arg("Password")), String(server.arg("IP")), String(server.arg("GW")));
}
//Write data to memory
/**
   We prepping the data strings by adding the end of line symbol I decided to use ";".
   Then we pass it off to the write_EEPROM function to actually write it to memmory
*/
void write_to_Memory(String s, String p, String i, String g) {
  s += ";";
  write_EEPROM(s, 0);
  p += ";";
  write_EEPROM(p, 100);
  i += ";";
  write_EEPROM(i, 200);
  g += ";";
  write_EEPROM(g, 220);
  EEPROM.commit();
}
//write to memory
void write_EEPROM(String x, int pos) {
  for (int n = pos; n < x.length() + pos; n++) {
    EEPROM.write(n, x[n - pos]);
  }
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  message += "<H2><a href=\"/\">go home</a></H2><br>";
  server.send(404, "text/plain", message);
}

String eprom()
{
  Serial.print("\nssid 1 : ");
  for (int addr = 0; addr < 22; addr++)
  {
    const char ssid1 (EEPROM.read(addr));    //Read from address 0x00


    Serial.print(ssid1);

  }
  Serial.print("\nPassword 1 : ");
  for (int addr = 100; addr < 120; addr++)
  {
    const char pass (EEPROM.read(addr));   //Read from address 0x00

    Serial.print(pass);


  }
  Serial.print("\nIP addresss1 :");
  for (int addr = 200; addr < 216; addr++)
  {
    const char ip (EEPROM.read(addr));    //Read from address 0x00

    Serial.print(ip);

  }
}



int bootmode() {

  int addr = 1;
  int temp = digitalRead(reset_mode);
  if (temp == HIGH)
  {
    EEPROM.write(addr, 1);
  }
  else
  {
    EEPROM.write(addr, 0);

  }
}

#include <ESP8266WiFi.h>
#include "emedwifi.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
DateTime now;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int reset_mode = 13;
int ledpin = 12;

RTC_DS3231 rtc;

const char INDEX_HTML[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta content=\"text/html; charset=ISO-8859-1\""
  " http-equiv=\"content-type\">"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<title>Wifi Configuration</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "</style>"
  "</head>"
  "<body>"
  "<h1>RESET MODE</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<P>"
  "<label>ssid:&nbsp;</label>"
  "<input maxlength=\"30\" name=\"ssid\"><br>"
  "<label>Password:&nbsp;</label><input maxlength=\"30\" name=\"Password\"><br>"
  "<label>IP:&nbsp;</label><input maxlength=\"15\" name=\"IP\"><br>"
  "<label>Gateway:&nbsp;</label><input maxlength=\"3\" name=\"GW\"><br>"
  "<INPUT type=\"submit\" value=\"Send\"> <INPUT type=\"reset\">"
  "</P>"
  "</FORM>"
  "</body>"
  "</html>";





void setup()
{
  pinMode(ledpin, OUTPUT);
  pinMode(reset_mode, INPUT);// declare push button as input
  EEPROM.begin(512);//Starting and setting size of the EEPROM
  Serial.begin(115200);

  server.begin();
  Serial.println("HTTP server started");
  delay(10);
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
  showDate();
  server.handleClient();

  int temp = digitalRead(reset_mode);

  /**IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);**/
  //Configuring the web server


}


void loop()
{

  int temp = digitalRead(reset_mode);


  server.handleClient();


  if (temp == 1) {
    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);
    Serial.println("HTTP server started");

    Serial.print("\nServer Started on RESET MODE");
    //resetMode();
    digitalWrite(ledpin, HIGH);
  }
  else
  {
    Serial.print("\nNORMAL MODE");
    delay(1000);
    digitalWrite(ledpin, LOW);
  }
  /**IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);**/
  //Configuring the web server
  delay(100);


}



void resetMode()

{
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
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



String aqi_weather_api () {


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
  String input = "";
  while (client.available()) {
    input += client.readStringUntil('\r');
    Serial.print(input);
  }
  //Serial.println("TEST");
  input = input.substring(input.indexOf('{'));
  //Serial.print(input);
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
  Serial.print("Date & Time  :");
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


void showDate()
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

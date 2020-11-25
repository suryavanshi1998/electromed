#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <Wire.h>
#include "RTClib.h"
#include <WiFiUdp.h>
//#include <DHT.h>
//#include <FS.h>
#define trigger 13
#define LED 12
#define power 14
//#define DHTPin 2
//#define DHTTYPE DHT22
//DHT dht(DHTPin, DHTTYPE);

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
//const long utcOffsetInSeconds = 28800;
const int ledPin =  12; // the LED pin number connected
int ledState = LOW;             // used to set the LED state

DateTime now;

RTC_DS3231 rtc;



//String SendHTML(float TemperatureWeb, float HumidityWeb, String TimeWeb, String DateWeb);

String Temperature;
String Humidity;
String formattedTime;
String Date;
int D;
int Mo;
int Y;


void setup()
{
  Serial.begin(115200);
  Wire.begin();
  pinMode(trigger, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(power, OUTPUT);
  Serial.println("wifi mode");
  delay(1000);
    ResetSettings();
  
    String returnedString = aqi_weather_api ();
    delay(1000);
    json_parse (returnedString);
    delay(1000);
    String returned_String = time_api ();
    //Serial.println(returnedString);
    delay(1000);
    String returned_DateTime =  json_parse_time (returned_String);
    delay(1000);
    webpage();
    // Serial.print(returned_DateTime);
   // rtc_time(returned_DateTime);
   // show();
  



}
void loop() {

  server.handleClient();
 // ResetSettings();
  delay(1000);
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(power, HIGH);


    digitalWrite(LED, HIGH);
   // millis_api();
    /* String returnedString = aqi_weather_api ();
      //Serial.println(returnedString);
      delay(1000);

      json_parse (returnedString);
      delay(1000);

      String returned_String = time_api ();
      //Serial.println(returnedString);
      delay(1000);

      String returned_DateTime =  json_parse_time (returned_String);
      delay(1000);
      //  Serial.print("test....");
      // Serial.print(returned_DateTime);
      rtc_time(returned_DateTime);
      show();*/

  }
  else {
    digitalWrite(LED, LOW);
  }
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
    //Serial.print(input);
  }
  //Serial.println("TEST");
  input = input.substring(input.indexOf('{'));
  Serial.print(input);
  return input;

}



String json_parse (String input) {
  // void apirequest ();
  // Serial.println(input2);
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(input);



  String status = root["status"];
  status = root["status"].as<String>();
  root["status"] = status;

  //  Temperature = root["data"]["temp"];
  Temperature = root["data"]["temp"].as<String>();
  root["data"]["temp"] = Temperature;

  //Humidity  = root["data"]["aqiParams"][5]["value"];
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
  Serial.print(Temperature);
  Serial.print("\n");
  Serial.print("humidity-->");
  Serial.print(Humidity);
  Serial.print("\n");
  Serial.print("wind speed-->");
  Serial.print(wind_speed);
  Serial.print("\n");
  Serial.print("wind direction-->");
  Serial.print(wind_direction);
  return Temperature, Humidity;

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
  char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
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

void ResetSettings() {


  char static_ip[16] = "192.168.1.184";
  char static_gw[16] = "192.168.1.1";
  char static_sn[16] = "255.255.255.0";
  if (digitalRead(trigger) == HIGH) {
    delay(500);

    digitalWrite(power, HIGH);
    WiFiManager wifiManager;
    wifiManager.resetSettings();


    IPAddress _ip, _gw, _sn;
    _ip.fromString(static_ip);
    _gw.fromString(static_gw);
    _sn.fromString(static_sn);


    wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);
    wifiManager.autoConnect("Electro-Med wifi manager");
    Serial.println("connected :)");
  }
}

void millis_api() {
  const long period = 60000;
  unsigned long previousMillis = 0;  //will store last time LED was blinked
  unsigned long currentMillis = millis(); // store the current time
  if ((currentMillis - previousMillis)  >= period) { // check if 1000ms passed

    String returnedString = aqi_weather_api ();
    //Serial.println(returnedString);
    delay(1000);

    json_parse (returnedString);
    delay(1000);

    String returned_String = time_api ();
    //Serial.println(returnedString);
    delay(1000);

    String returned_DateTime =  json_parse_time (returned_String);
    delay(1000);
    //  Serial.print("test....");
    // Serial.print(returned_DateTime);
    rtc_time(returned_DateTime);
    show();

    webpage();
    previousMillis = currentMillis;
  }
}

void webpage() {

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();


}

void handle_OnConnect() {


  //  Date = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Temperature = Temperature;
  Humidity = Humidity;
  server.send(200, "text/html", SendHTML(Temperature, Humidity, formattedTime, Date));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}


String SendHTML(String TemperatureWeb, String HumidityWeb, String TimeWeb, String DateWeb) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP8266 Global Server</title>\n";

  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>ESP8266 Global Server</h1>\n";

  ptr += "<p>Date: ";
  ptr += (String)DateWeb;
  ptr += "</p>";
  ptr += "<p>Time: ";
  ptr += (String)TimeWeb;
  ptr += "</p>";
  ptr += "<p>Temperature: ";
  ptr += (String)TemperatureWeb;
  ptr += "C</p>";
  ptr += "<p>Humidity: ";
  ptr += (String)HumidityWeb;
  // ptr += "%</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

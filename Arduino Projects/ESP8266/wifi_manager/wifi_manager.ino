#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <Wire.h>
#include "RTClib.h"
#define trigger 13
#define LED 12
#define power 14


char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

RTC_DS3231 rtc;
DateTime now;
void setup() {



#ifdef ARDUINO_ARCH_AVR
  int inttmp = 32123;
#else
  // too long for AVR 16 bits!
  int inttmp = 24543557;
#endif
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  pinMode(trigger, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(power, OUTPUT);
  delay(5000);
  if (digitalRead(trigger) == HIGH) {
    digitalWrite(power, HIGH);
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("CIRCUIT DIGEST WiFi Manager");
    Serial.println("connected :)");
  }
}
void loop() {
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(power, LOW);
    while (WiFi.status() == WL_CONNECTED) {
      digitalWrite(LED, HIGH);
      delay(500);
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
    }
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

/*Smart Plug - Captive Portal Home Automation 
 * Requires no Wi-Fi to operate
 * Date:19-8-2019
 * Author: B.Aswinth Raj
 * Website: Electro-Med.com 
 */

//Download all required header filers from Electro-Med.com 
#include <ESP8266WiFi.h>
#include "DNSServer.h"  
#include <ESP8266WebServer.h>

const byte        DNS_PORT = 53;          // 53 is set as DNS port
IPAddress         apIP(10, 10, 10, 1);    // Network Server
DNSServer         dnsServer;              // DNS server object
ESP8266WebServer  webServer(80);          // Webserver object 

int GPIO_2 = 2; //Pin defanition - Relay will be connected to GPIO-0

/*START OF HMTL CODE*/
String style_detials =  //This String defines the style attributes for webpage
   "<style type=\"text/css\">"
   " body{"
    "  background-color: #a69695;"
    "}"
    "button{"
     " display: inline-block;"
    "}"
    "#buttons{"
     " text-align: center;"
    "}"

    ".controllButtons{"
     " margin-top: 15px;"
      "margin-left: 5px;"
      "background-color: white;"
      "padding: 10px;"
      "border:1px solid black;"
      "border-radius: 10px;"
      "cursor: pointer;"
      "font-size: 14px;"
    "}"

    ".controllButtons:hover{"
     " background-color: orange;"
      "padding: 10px;"
      "border:1px solid black;"
      "border-radius: 10px;"
      "cursor: pointer;"
      "font-size: 14px;"
    "}"

    "@media only screen and (max-width: 700px) {"
     " button{"
      "  display: block;"
      "}"
      "#buttons{"
       " margin-top: 10%;"
        "margin-left: 35%;"
      "}"
       " .controllButtons{"
        "  margin-top: 15px;"
        "margin-left: 5px;"
        "background-color: white;"
        "padding: 15px;"
        "border:1px solid black;"
        "border-radius: 10px;"
        "cursor: pointer;"
        "font-size: 16px;"
      "}"

      ".controllButtons:hover{"
       " background-color: orange;"
        "padding: 15px;"
        "border:1px solid black;"
        "border-radius: 10px;"
        "cursor: pointer;"
        "font-size: 16px;"
      "}"
    "}"

  "</style>";

String Home_Screen = "" //Page 1 - Home Screen HTML code
                      "<!DOCTYPE html><html>"
                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                      + style_detials +
                      "<div id=\"buttons\">"
                      "<a style=\"text-decoration:none;\" href=\"relay_ON\"> <button id=\"switchLight1\" class=\"controllButtons\">Turn ON</button> </a>"
                      "<a style=\"text-decoration:none;\" href=\"relay_OFF\"><button id=\"switchLight2\" class=\"controllButtons\">Turn OFF</button>  </a>"
                      "</div>"
                      "<body><h1>Welcome - Electro-Med</h1>"
                      "</body></html>";

String ON_Screen = "" //Page 2 - If device is turned ON
                      "<!DOCTYPE html><html>"
                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                      + style_detials +
                      "<div id=\"buttons\">"
                      "<a style=\"text-decoration:none;\" href=\"relay_ON\"> <button id=\"switchLight1\" class=\"controllButtons\">Turn ON</button> </a>"
                      "<a style=\"text-decoration:none;\" href=\"relay_OFF\"><button id=\"switchLight2\" class=\"controllButtons\">Turn OFF</button>  </a>"
                      "</div>"
                      "<body><h1>Smart Plug - Turned ON</h1>"
                      "</body></html>";

String OFF_Screen = "" //Page 3 - If device is turned OFF
                      "<!DOCTYPE html><html>"
                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                      + style_detials +
                      "<div id=\"buttons\">"
                      "<a style=\"text-decoration:none;\" href=\"relay_ON\"> <button id=\"switchLight1\" class=\"controllButtons\">Turn ON</button> </a>"
                      "<a style=\"text-decoration:none;\" href=\"relay_OFF\"><button id=\"switchLight2\" class=\"controllButtons\">Turn OFF</button>  </a>"
                      "</div>"
                      "<body><h1>Smart Plug - Turned OFF</h1>"
                      "</body></html>";
                      
/*END OF HMTL CODE*/                    
                      

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //LED pin as output for indication 
  pinMode(GPIO_2, OUTPUT); //GPIO pin as output for Relay control 
    
  WiFi.mode(WIFI_AP); //Set ESP in AP mode
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Electromed_Smart_Switch"); // Name your AP network 

  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.onNotFound([]() {
    webServer.sendHeader("Location", String("http://www.Electro-Med.com/home.html"), true); //Open Home screen by default 
    webServer.send ( 302, "text/plain", "");
  });
  
  webServer.on("/home.html", []() {
    webServer.send(200, "text/html", Home_Screen);
  });

//ON_Screen
  webServer.on("/relay_ON", [](){ //If turn on Button is pressed 
       digitalWrite(LED_BUILTIN, LOW); //Turn off LED
       digitalWrite(GPIO_2, HIGH);  //Turn off Relay 
       webServer.send(200, "text/html", ON_Screen); //Display this screen 
  });

//OFF_Screen
  webServer.on("/relay_OFF", [](){ //If turn off Button is pressed 
       digitalWrite(LED_BUILTIN, HIGH); //Turn on LED
       digitalWrite(GPIO_2, LOW); //Turn on Relay 
       webServer.send(200, "text/html", OFF_Screen); //Display this screen
  });

  
  
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid     = "SHUBHAM BOYS HOSTAL";
const char* password = "Shubham@99";
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional


  
ESP8266WebServer server(80);
 
//Handles http request 
void handleRoot() {
  digitalWrite(2, 0);   //Blinks on board led on page request 
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(2, 1);
}
 
 
// the setup function runs once when you press reset or power the board
void setup() {
  
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  
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
   if(WiFi.status() == WL_CONNECTED) //If WiFi connected to hot spot then start mDNS
  {
    if (MDNS.begin("www.esp8266.emed.com")) {  //Start mDNS with name esp8266
      Serial.println("MDNS started");
    }
  }
 
  server.on("/", handleRoot);  //Associate handler function to path
    
  server.begin();                           //Start server
  Serial.println("HTTP server started");
}
 
// the loop function runs over and over again forever
void loop() {
  server.handleClient();
}

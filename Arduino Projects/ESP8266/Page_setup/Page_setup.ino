#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "arduino_secret.h"
#include <EEPROM.h>

#include "page1.h"
#include "page2.h"
//#include "page3.h"

ESP8266WebServer server(80);

void handleRoot() {
  Serial.println("GET /");
  server.send(200, "text/html", htmlPage1);
}

void handlePage2() {
  Serial.println("GET /page2");
  if (server.hasArg("ssid")&& server.hasArg("Password")&& server.hasArg("IP")&&server.hasArg("GW") ) {//If all form fields contain data call handelSubmit()
    handleSubmit();
  }
  else {//Redisplay the form
  server.send(200, "text/html", htmlPage2);
}
}
void handleSubmit(){//dispaly values and write to memmory
  String response="<p>The ssid is ";
 response += server.arg("ssid");
 response +="<br>";
 response +="And the password is ";
 response +=server.arg("Password");
 response +="<br>";
 response +="And the IP Address is ";
 response +=server.arg("IP");
 response +="</P><BR>";
 response +="<H2><a href=\"/\">go home</a></H2><br>";

 server.send(200, "text/html", response);
 //calling function that writes data to memory 
 write_to_Memory(String(server.arg("ssid")),String(server.arg("Password")),String(server.arg("IP")),String(server.arg("GW")));
}
//Write data to memory
/**
 * We prepping the data strings by adding the end of line symbol I decided to use ";". 
 * Then we pass it off to the write_EEPROM function to actually write it to memmory
 */
void write_to_Memory(String s,String p,String i, String g){
 s+=";";
 write_EEPROM(s,0);
 p+=";";
 write_EEPROM(p,100);
 i+=";";
 write_EEPROM(i,200); 
 g+=";";
 write_EEPROM(g,220); 
 EEPROM.commit();
}
//write to memory
void write_EEPROM(String x,int pos){
  for(int n=pos;n<x.length()+pos;n++){
     EEPROM.write(n,x[n-pos]);
  }
}





/*
void handlePage3() {
  Serial.println("GET /page3");
  server.send(200, "text/html", htmlPage3);
}
*/
void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/page2", handlePage2);
 // server.on("/page3", handlePage3);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

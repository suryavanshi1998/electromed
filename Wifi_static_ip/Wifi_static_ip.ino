/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-static-fixed-ip-address-arduino/
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>
int addr = 0;

// Replace with your network credentials
const char* ssid     = "emed@17vnpuri";
const char* password = "D17vnpuri";

// Set web server port number to 80
//WiFiServer server(80);
ESP8266WebServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
//String output5State = "off";
//String output4State = "off";

// Assign output variables to GPIO pins
//const int output5 = 5;
//const int output4 = 4;


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


const char INDEX_HTML[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta content=\"text/html; charset=ISO-8859-1\""
" http-equiv=\"content-type\">"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>ESP8266 Web Form Demo</title>"
"<style>"
"\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
"</style>"
"</head>"
"<body>"
"<h1>ESP8266 Web Form Demo</h1>"
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




void setup() {
  EEPROM.begin(512);  //Initialize EEPROM
  Serial.begin(115200);
  // Initialize the output variables as outputs
 // pinMode(output5, OUTPUT);
 // pinMode(output4, OUTPUT);
  // Set outputs to LOW
 // digitalWrite(output5, LOW);
 // digitalWrite(output4, LOW);
  
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
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();//Checks for web server activity
  
}
//Dealing with the call to root
void handleRoot() {
   if (server.hasArg("ssid")&& server.hasArg("Password")&& server.hasArg("IP")&&server.hasArg("GW") ) {//If all form fields contain data call handelSubmit()
    handleSubmit();
  }
  else {//Redisplay the form
    server.send(200, "text/html", INDEX_HTML);
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
 write_EEPROM(p,15);
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

void eprom_read(int addr, int i)
{
   //Initialize EEPROM
  //Serial.begin(9600); //Serial communication to display data
  // read appropriate byte of the EEPROM.  
  Serial.println(""); //Goto next line, as ESP sends some garbage when you reset it  
  Serial.print(char(EEPROM.read(addr)));    //Read from address 0x00
  addr++;                      //Increment address
  Serial.print(char(EEPROM.read(addr)));    //Read from address 0x01
  addr++;                      //Increment address
  Serial.println(char(EEPROM.read(addr)));    //Read from address 0x02
 
  //Read string from eeprom
  String www;   
  //Here we dont know how many bytes to read it is better practice to use some terminating character
  //Lets do it manually www.circuits4you.com  total length is 20 characters
  for(int i=0;i<30;i++) 
  {
    www = www + char(EEPROM.read(0x0F+i)); //Read one by one with starting address of 0x0F    
  }  
 
  Serial.print(www);  //Print the text on serial monitor
}




//Shows when we get a misformt or wrong request for the web server
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  message +="<H2><a href=\"/\">go home</a></H2><br>";
  server.send(404, "text/plain", message);
}

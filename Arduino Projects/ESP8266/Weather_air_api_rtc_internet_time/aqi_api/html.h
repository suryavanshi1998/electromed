String SendHTML(String TemperatureWeb, String HumidityWeb, String Wind_speedWeb, String Wind_directionWeb, String TimeWeb, String DateWeb) {
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
  ptr += "<p>Wind Direction: ";
  ptr += (String)Wind_directionWeb;
  ptr += "<p>Wind Speed: ";
  ptr += (String)Wind_speedWeb;
  // ptr += "%</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
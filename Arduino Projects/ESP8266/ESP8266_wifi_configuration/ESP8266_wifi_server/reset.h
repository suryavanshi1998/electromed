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
  "<h3> SSID and Password length must be less than 20 characters"
  "<FORM action=\"/\" method=\"post\">"
  "<P>"
  "<label>ssid:&nbsp;</label>"
  "<input maxlength=\"20\" name=\"ssid\"><br>"
  "<label>Password:&nbsp;</label><input maxlength=\"20\" name=\"Password\"><br>"
  "<label>IP:&nbsp;</label><input maxlength=\"15\" name=\"IP\">  <value var =\" document.getElementById('IP').value\"><br>"
  "<label>Gateway:&nbsp;</label><input maxlength=\"6\" name=\"GW\"><br>"
  "<INPUT type=\"submit\" value=\"Send\"> <INPUT type=\"reset\">"
  "</P>"
  "</FORM>"
  "</body>"
  "</html>";


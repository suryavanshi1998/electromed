const char htmlPage2[] PROGMEM = R"=====(
<html>

<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <title>Hello from HTTP Server ESP8266 - Page1</title>

    <meta content=\"text/html; charset=ISO-8859-1\"
     http-equiv=\"content-type\">
    <meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">
    <title>ESP8266 Web Server</title>
    <style>"
    \"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\"
</style>
</head>
</head>

<body>
    <h1>ESP8266 Web Form Demo</h1>
    <FORM action=\"/\" method=\"post\">
        "<P>"
    <label>ssid:&nbsp;</label>
    <input maxlength=\"30\" name=\"ssid\"><br>
    <label>Password:&nbsp;</label><input maxlength=\"30\" name=\"Password\"><br>
    <label>IP:&nbsp;</label><input maxlength=\"15\" name=\"IP\"><br>
    <label>Gateway:&nbsp;</label><input maxlength=\"3\" name=\"GW\"><br>
    <INPUT type="submit" value="Send"/> <INPUT type="reset"/>
    </P>
    </FORM>

    <div class="container">
        <h2>ESP8266 HTTP Server</h2>
        <p>Electro-Med ESP8266 HTTP Server</p>
        <p>
            <a class="btn btn-primary" href="/" role="button">Home</a>
            
        </p>

        <p>Copyright (C) 2020 <a href="https://www.electromed.co.in">Electro-Med</a>.</p>
    </div>
</body>

</html>
)=====";
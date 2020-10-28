const char htmlPage1[] PROGMEM = R"=====(
<html>

<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <title>Hello from HTTP Server ESP8266Electro-Med ESP8266 HTTP Server - home page</title>
</head>

<body>
    <div class="container">
        <h1>ESP8266 HTTP Server</h1>
        <p>Electro-Med ESP8266 HTTP Server.</p>
        <p>
            
            <a class="btn btn-primary" href="/page2" role="button">Settings</a>
            <a class="btn btn-primary" href="/page3" role="button">Data</a>
        </p>

        <p>Copyright (C) 2020 <a href="https://www.electromed.co.in">Electro-Med</a>.</p>
    </div>
</body>

</html>
)=====";
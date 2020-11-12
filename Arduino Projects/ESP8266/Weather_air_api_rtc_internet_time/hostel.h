// ESP8266 Core: 2.5.0
// Windows
//
// Find file 'c:\Users\[your name]\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.5.0\platform.txt'. 
// In the same directory create file 'platfom.local.txt'. Insert text
// 'compiler.cpp.extra_flags=-D_SSID="xxx" -D_PWD="xxx"' into the file.
//
// Or change the parameters in this file.

#if defined(_SSID)
  const char* ssid     = _SSID;
  const char* password = _PWD;
#else
	 const char* ssid     = "SHUBHAM BOYS HOSTAL";
	 const char* password = "Shubham@99";
	 IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
	IPAddress gateway(192, 168, 1, 1);

	IPAddress subnet(255, 255, 0, 0);
	IPAddress primaryDNS(8, 8, 8, 8);   //optional
	IPAddress secondaryDNS(8, 8, 4, 4); //optional
#endif

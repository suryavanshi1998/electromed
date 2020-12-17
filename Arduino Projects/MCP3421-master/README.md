# MCP3421

From: http://interface.khm.de/index.php/lab-log/connect-a-mcp3421-18-bit-analog-to-digital-converter-to-an-arduino-board/

Functions of the MCP3421 Library

 

	init(address,sr,pga);

 

	address = 0x68;  // MCP3421 device address

	sr= Sample Rate Selection
	sr=0 ; 00 = 240 SPS (12 bits)
	sr=1 ; 01 = 60 SPS (14 bits)

	sr=2 ; 10 = 15 SPS (16 bits)
	sr=3 ; 11 = 3.75 SPS (18 bits)

	 

	pga= PGA Gain Selector
	0 = 1 V/V
	1 = 2 V/V 
	2 = 4 V/V
	3 = 8 V/V

	 

	int ready()
	// returns 1 when conversion is ready

	 

	long getLong()
	// returns conversion result as long number

	 

	double getDouble()
	// returns  voltage as double/float number


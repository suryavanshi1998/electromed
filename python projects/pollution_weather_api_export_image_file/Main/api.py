

import requests
import json
import array as arr
import time
from text_to_image import genAirQualityImage,genAaqi,temp_hum,windImage



def get_data_via_api():
	

	r = requests.get("http://api.airpollutionapi.com/1.0/aqi?lat=25.302547&lon=82.983220&APPID=qsfmma0bkgr296g79ogrhfubg5")
	res = r.json()
		
		  
	
	
	#print(res)
		 
	# Extract specific node content.
	#quality = res['data']['text']
	#print("QUALITY:",quality)

	#alert = res['data']['alert']
	#print("Alert:",alert)

	#print("Country:",res['data']['country'])
	#print("LOCATION",res['data']['source']['name'])
	#print(res['data']['aqiParams'])
	aqiParams = res['data']['aqiParams']
	#print(aqiParams)

	raw_no2= aqiParams[0]["value"]
	no2_split = raw_no2.split(", ")
	try:
		NO2 = no2_split[0]
		pass
	except Exception as e:
		NO2 = '..........'
		raise e
		
		

	#print("NO2>>",NO2)


	raw_O3= aqiParams[1]["value"]
	split_O3 = raw_O3.split(", ")
	try:
		O3 = split_O3[0]
		pass
	except Exception as e:
		O3 = '..........'
		raise e
		
	#print("O3>>",O3)



	try:
		integer_aqi = aqiParams[0]["aqi"]
		aqi = str(integer_aqi)
		pass
	except Exception as e:
		aqi = '..........'
		raise e
	#print("AQI:",aqi)

		
	raw_pm2_5 = aqiParams[2]["value"]
	split_pm2_5 = raw_pm2_5.split(",")
	try:
		PM2_5 = split_pm2_5[0]
		pass
	except Exception as e:
		PM2_5 = '..........'
		raise e
		
	#print("PM2.5>>",PM2_5)
		
	try:
		tempreture = res['data']['temp']
		pass
	except Exception as e:
		tempreture = '..........'
		raise e
		
	#print("Temprature:",tempreture)

	try:
		humidity = aqiParams[3]["value"]
		pass
	except Exception as e:
		humidity = '..........'
		raise e
		
	#print("Humidity:",humidity)

	try:
		wind_speed = aqiParams[5]["value"]
		pass
	except Exception as e:
		wind_speed = '..........'
		raise e
		
	#print("wind speed:",wind_speed)

	try:
		wind_direction = aqiParams[6]["value"]
		pass
	except Exception as e:
		wind_speed = '..........'
		raise e


	aqi0 = aqiParams[0]["aqi"]
	aqi1 = aqiParams[1]["aqi"]
	aqi2 = aqiParams[2]["aqi"]
	
	if aqi0>=aqi1 and aqi0>=aqi2:
		integer_aqi=aqi0
		primary_pollutant = 'NO2'

	elif aqi1>=aqi0 and aqi1>=aqi2:
	 	integer_aqi=aqi1
	 	primary_pollutant = 'O3'
	elif aqi2>=aqi0 and aqi2>=aqi1:
		integer_aqi=aqi2
		primary_pollutant = 'pm2.5'
	 	

	aqi = str(integer_aqi)
	


	data = { 

						"NO2":NO2,
		 				"AQI":aqi, 
		 				"O3":O3, 
		 				"PM2_5":PM2_5, 
		 				"primary_pollutant":primary_pollutant,
		 				"Tempreture":tempreture, 
		 				"Humidity":humidity, 
		 				"Wind_speed":wind_speed,
		 				"Wind_direction":wind_direction

	}

	a = str(data)
		
	file = open("output.txt", "w")
	file.write(a)
	file.close()			
							
	return data

data = get_data_via_api()

'''
#used only for constant data 
data = { 

						"NO2":"NO2",
		 				"AQI":"aqi", 
		 				"O3":"O3", 
		 				"PM2_5":"PM2_5", 
		 				"primary_pollutant":"primary_pollutant",
		 				"Tempreture":"tempreture", 
		 				"Humidity":"humidity", 
		 				"Wind_speed":"wind_speed",
		 				"Wind_direction":"wind_direction"

	}
'''
genAirQualityImage(data)
genAaqi (data)
windImage(data)
temp_hum (data)
	


#weather_api()

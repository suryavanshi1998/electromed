import requests
import json
import array as arr
import time
from text_to_image_final import image_air_quality, image_weather



def weather_api():

	while(1):

 
		r = requests.get("http://api.airpollutionapi.com/1.0/aqi?lat=25.290964&lon=83.004257&APPID=qsfmma0bkgr296g79ogrhfubg5")
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
		
		

		print("NO2>>",NO2)


		raw_O3= aqiParams[1]["value"]
		split_O3 = raw_O3.split(", ")
		try:
			O3 = split_O3[0]
			pass
		except Exception as e:
			O3 = '..........'
			raise e
		
		print("O3>>",O3)



		try:
			integer_aqi = aqiParams[0]["aqi"]
			aqi = str(integer_aqi)
			pass
		except Exception as e:
			aqi = '..........'
			raise e
		print("AQI:",aqi)

		
		raw_pm2_5 = aqiParams[2]["value"]
		split_pm2_5 = raw_pm2_5.split(",")
		try:
			PM2_5 = split_pm2_5[0]
			pass
		except Exception as e:
			PM2_5 = '..........'
			raise e
		
		print("PM2.5>>",PM2_5)
		
		try:
			tempreture = res['data']['temp']
			pass
		except Exception as e:
			tempreture = '..........'
			raise e
		
		print("Temprature:",tempreture)

		try:
			humidity = aqiParams[3]["value"]
			pass
		except Exception as e:
			humidity = '..........'
			raise e
		
		print("Humidity:",humidity)

		try:
			wind_speed = aqiParams[5]["value"]
			pass
		except Exception as e:
			wind_speed = '..........'
			raise e
		
		print("wind speed:",wind_speed)

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
		print("AQI0-->>",aqi0)
		print("AQI1-->>",aqi1)
		print("AQI2-->>",aqi2)
		print("COMPARED AQI",aqi)
		print("wind direction:",wind_direction)
		print("primary pollutant-->>",primary_pollutant)

		extract_data = { 

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

		image_air_quality (extract_data)
		image_weather (extract_data)
		time.sleep(3600)
	pass
weather_api ()






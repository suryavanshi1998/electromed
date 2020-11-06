from PIL import Image, ImageDraw, ImageFont
#from json_test import*
import time


def image_air_quality (extract_data ):

	no2= extract_data["NO2"]
	aqi= extract_data["AQI"]
	O3= extract_data["O3"]
	pm2_5= extract_data["PM2_5"]
	Primary_pollutant = extract_data["primary_pollutant"]

	print("TEST AQI",aqi)
	# get an image
	base = Image.open('background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	txt = Image.new('RGBA', base.size, (205,205,205,0))

	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	font1 = ImageFont.truetype(r'REFSAN.ttf', 12) 
	font2 = ImageFont.truetype(r'REFSAN.ttf', 10) 
	d = ImageDraw.Draw(txt)
	d.text((40,2), "Cantonment Board Varanasi",font=font1, fill=(205,205,205,205))
	d.text((55,15), "Air Quality Parameters",font=font1, fill=(205,205,205,205))

	d.text((20,30), "Primary Pollutant:",font=font1, fill=(205,205,205,205))
	d.text((138,30), Primary_pollutant,font=font1, fill=(205,205,205,205))

	d.text((20,86), "NO2:",font=font1, fill=(205,205,205,205))
	d.text((138,86), no2, font=font1,fill=(205,205,205,205))

	d.text((20,68), "O3:",font=font1, fill=(205,205,205,205))
	d.text((138,68), O3,font=font1, fill=(205,205,205,205))

	d.text((20,104), "AQI:",font=font1, fill=(205,205,205,205))
	d.text((138,104), aqi,font=font1, fill=(205,205,205,205))

	d.text((20,50), "PM2.5:",font=font1, fill=(205,205,205,205))
	d.text((138,50), pm2_5,font=font1, fill=(205,205,205,205))
	
	out1 = Image.alpha_composite(base, txt)
	out1.show()
	out1.save("output_air_quality.png") 
	#time.sleep(5)
	#out1.close()

	#whether_api ()


#whether_api ()
	#return;


def image_weather (extract_data):

	tempreture= extract_data["Tempreture"]
	humidity= extract_data["Humidity"]
	wind_speed= extract_data["Wind_speed"]
	wind_direction= extract_data["Wind_direction"]


	# get an image
	base = Image.open('background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	txt = Image.new('RGBA', base.size, (205,205,205,0))

	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	font1 = ImageFont.truetype(r'REFSAN.ttf', 12) 
	font2 = ImageFont.truetype(r'REFSAN.ttf', 12) 
	d = ImageDraw.Draw(txt)
	d.text((40,10), "Cantonment Board Varanasi",font=font1, fill=(205,205,205,205))
	d.text((40,25), "Ambient Whether Parameters",font=font1, fill=(205,205,205,205))


	d.text((20,45), "Tempreture:",font=font2, fill=(205,205,205,205))
	d.text((130,45), tempreture,font=font2, fill=(205,205,205,205))
	d.text((150,45), "°C",font=font2, fill=(205,205,205,205))


	d.text((20,68), "Humidity:",font=font2, fill=(205,205,205,205))
	d.text((130,68), humidity,font=font2, fill=(205,205,205,205))




	d.text((20,86), "Wind Speed:",font=font2, fill=(205,205,205,205))
	d.text((130,86), wind_speed, font=font2,fill=(205,205,205,205))

	d.text((20,104), "Wind Direction:",font=font2, fill=(205,205,205,205))
	d.text((130,104), wind_direction,font=font2, fill=(205,205,205,205))


	out2 = Image.alpha_composite(base, txt)

	out2.show()
	out2.save("output_weather.png") 



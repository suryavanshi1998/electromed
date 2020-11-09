from PIL import Image, ImageDraw, ImageFont
#from json_test import*
import time
from datetime import datetime

now = datetime.now()
current_time = now.strftime("%H:%M:%S")

def genAirQualityImage (data):

	no2= data["NO2"]
	#aqi= data["AQI"]
	O3= data["O3"]
	pm2_5= data["PM2_5"]
	#Primary_pollutant = data["primary_pollutant"]

	#print("TEST AQI",aqi)
	# get an image
	base = Image.open('/home/pi/Desktop/main/background/background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	txt = Image.new('RGBA', base.size, (205,205,205,0))

	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	font3 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 60)
	
	font2 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf",14)
	font1 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 15)
	d = ImageDraw.Draw(txt)
	d.text((2,2), "Cantonment Board Varanasi",font=font2, fill=(205,205,205,205))
	d.text((14,15), "Air Quality Parameters",font=font1, fill=(205,205,205,205))
	#d.text((10,30), "Time :",font=font1, fill=(205,205,205,205))
	d.text((10,32), current_time,font=font1, fill=(205,205,205,205))
	d.text((10,86), "NO2:",font=font1, fill=(205,205,205,205))
	d.text((110,86), no2, font=font1,fill=(205,205,205,205))

	d.text((10,68), "O3:",font=font1, fill=(205,205,205,205))
	d.text((110,68), O3,font=font1, fill=(205,205,205,205))


	d.text((10,50), "PM2.5:",font=font1, fill=(205,205,205,205))
	d.text((110,50), pm2_5,font=font1, fill=(205,205,205,205))
	out1 = Image.alpha_composite(base, txt)
	#out1.show()
	out1.save("/home/pi/Desktop/main/output/airImage.png") 
	#time.sleep(5)
	#out1.close()

	#whether_api ()
def genAaqi (data):

	#no2=data["NO2"]
	aqi= data["AQI"]
	#O3= data["O3"]
	pm2_5= data["PM2_5"]
	Primary_pollutant = data["primary_pollutant"]

	#print("TEST AQI",aqi)
	# get an image
	base = Image.open('/home/pi/Desktop/main/background/background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	txt = Image.new('RGBA', base.size, (205,205,205,0))

	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	font2 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf",14)
	font1 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 15)
	d = ImageDraw.Draw(txt)
	font3 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 60)
	
	d.text((2,2), "Cantonment Board Varanasi",font=font2, fill=(205,205,205,205))
	d.text((14,15), "Air Quality Parameters",font=font1, fill=(205,205,205,205))
	#d.text((10,32), "Time :",font=font1, fill=(205,205,205,205))
	d.text((10,32), current_time,font=font1, fill=(205,205,205,205))
	d.text((10,50), "Primary",font=font1, fill=(205,205,205,205))
	d.text((10,65), "Pollutant :",font=font1, fill=(205,205,205,205))
	
	d.text((120,65), Primary_pollutant,font=font1, fill=(205,205,205,205))


	d.text((10,85), "AQI:",font=font1, fill=(205,205,205,205))
	d.text((120,85), aqi,font=font1, fill=(205,205,205,205))
	
	out1 = Image.alpha_composite(base, txt)
	#out1.show()
	out1.save("/home/pi/Desktop/main/output/aqiImage.png") 

#whether_api ()
	#return;


def temp_hum (data):

	tempreture= data["Tempreture"]
	humidity= data["Humidity"]
	#wind_speed= data["Wind_speed"]
	#wind_direction= data["Wind_direction"]


	# get an image
	base = Image.open('/home/pi/Desktop/main/background/background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	txt = Image.new('RGBA', base.size, (205,205,205,0))

	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	font3 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 60)
	font2 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf",15)
	font1 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 14)
	d = ImageDraw.Draw(txt)
	d.text((2,2), "Cantonment Board Varanasi",font=font1, fill=(205,205,205,205))
	d.text((12,15), "Air Quality Parameters",font=font2, fill=(205,205,205,205))
	#d.text((10,30), "Time :",font=font2, fill=(205,205,205,205))
	d.text((10,32), current_time,font=font2, fill=(205,205,205,205))

	d.text((10,48), "Tempreture:",font=font2, fill=(205,205,205,205))
	d.text((120,48), tempreture,font=font2, fill=(205,205,205,205))
	d.text((140,48), "deg.C",font=font2, fill=(205,205,205,205))


	d.text((10,68), "Humidity:",font=font2, fill=(205,205,205,205))
	d.text((120,68), humidity,font=font2, fill=(205,205,205,205))
	out2 = Image.alpha_composite(base, txt)

	#out2.show()
	out2.save("/home/pi/Desktop/main/output/temp_hum.png") 

def windImage(data):

	#tempreture= data["Tempreture"]
	#humidity= data["Humidity"]
	wind_speed= data["Wind_speed"]
	wind_direction= data["Wind_direction"]


	# get an image
	base = Image.open('/home/pi/Desktop/main/background/background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	txt = Image.new('RGBA', base.size, (205,205,205,0))

	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	font3 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 60)
	
	font2 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf",15)
	font1 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 14)
	d = ImageDraw.Draw(txt)
	d.text((2,2), "Cantonment Board Varanasi",font=font1, fill=(205,205,205,205))
	d.text((12,15), "Air Quality Parameters",font=font2, fill=(205,205,205,205))
	#d.text((10,32), "Time :",font=font, fill=(205,205,205,205))
	d.text((10,32), current_time,font=font2, fill=(205,205,205,205))
	
	d.text((10,48), "Wind Speed:",font=font2, fill=(205,205,205,205))
	d.text((100,48), wind_speed, font=font2,fill=(205,205,205,205))

	d.text((10,65), "Wind",font=font2, fill=(205,205,205,205))
	d.text((10,80), "Direction :",font=font2, fill=(205,205,205,205))
	d.text((100,80), wind_direction,font=font2, fill=(205,205,205,205))

	out2 = Image.alpha_composite(base, txt)

	#out2.show()
	out2.save("/home/pi/Desktop/main/output/wind_speed_dir.png") 

def gentime():
	base = Image.open('/home/pi/Desktop/main/background/background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	txt = Image.new('RGBA', base.size, (205,205,205,0))

	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	font3 = ImageFont.truetype("/home/pi/Desktop/main/fonts/Univers_65_Bold.ttf", 60)
	d = ImageDraw.Draw(txt)
	d.text((2,5), current_time,font=font3, fill=(205,205,205,205))

	out2 = Image.alpha_composite(base, txt)

	out2.show()
	out2.save("/home/pi/Desktop/main/output/time.png") 
gentime()

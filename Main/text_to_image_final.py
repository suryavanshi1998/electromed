from PIL import Image, ImageDraw, ImageFont
import PIL 
#from json_test import*
import time
from datetime import datetime



now = datetime.now()
current_time = now.strftime("%H:%M:%S")

def genAirQualityImage (data):
	large_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 60)
	medium_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 14)


	no2= data["NO2"]
	#aqi= data["AQI"]
	O3= data["O3"]
	pm2_5= data["PM2_5"]

	img = PIL.Image.new(mode ="RGBA", size = (197, 111), color=(0,0,0))
	
	
	d = ImageDraw.Draw(img)
	d.text((2,2), "Cantonment Board Varanasi",font=medium_font, fill=(255,255,255,255))
	d.text((14,15), "Air Quality Parameters",font=medium_font, fill=(255,255,255,255))
	d.text((10,86), "NO2:",font=medium_font, fill=(255,255,255,255))
	d.text((110,86), no2, font=medium_font,fill=(255,255,255,255))

	d.text((10,68), "O3:",font=medium_font, fill=(255,255,255,255))
	d.text((110,68), O3,font=medium_font, fill=(255,255,255,255))


	d.text((10,50), "PM2.5:",font=medium_font, fill=(255,255,255,255))
	d.text((110,50), pm2_5,font=medium_font, fill=(255,255,255,255))
	#img.show()
	img.save("output/airImage.png") 


def genAaqi (data):
	large_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 60)
	medium_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 14)

	#no2=data["NO2"]
	aqi= data["AQI"]
	#O3= data["O3"]
	pm2_5= data["PM2_5"]
	Primary_pollutant = data["primary_pollutant"]
	img = PIL.Image.new(mode ="RGBA", size = (197, 111),color=(0,0,0))
	
	
	
	d = ImageDraw.Draw(img)
	
	d.text((2,2), "Cantonment Board Varanasi",font=medium_font, fill=(255,255,255,255))
	d.text((14,15), "Air Quality Parameters",font=medium_font, fill=(255,255,255,255))
	
	d.text((10,50), "Primary",font=medium_font, fill=(255,255,255,255))
	d.text((10,65), "Pollutant :",font=medium_font, fill=(255,255,255,255))
	
	d.text((120,65), Primary_pollutant,font=medium_font, fill=(255,255,255,255))


	d.text((10,85), "AQI:",font=medium_font, fill=(255,255,255,255))
	d.text((120,85), aqi,font=medium_font, fill=(255,255,255,255))
	
	#img.show()
	img.save("output/aqiImage.png") 



def temp_hum (data):
	
	large_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 60)
	medium_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 14)
	tempreture= data["Tempreture"]
	humidity= data["Humidity"]
	
	img = PIL.Image.new(mode ="RGBA", size = (197, 111),color=(0,0,0))
	
	
	d = ImageDraw.Draw(img)

	d.text((2,2), "Cantonment Board Varanasi",font=medium_font, fill=(255,255,255,255))
	d.text((12,15), "Air Quality Parameters",font=medium_font, fill=(255,255,255,255))
	
	d.text((10,48), "Tempreture:",font=medium_font, fill=(255,255,255,255))
	d.text((120,48), tempreture,font=medium_font, fill=(255,255,255,255))
	d.text((140,48), "deg.C",font=medium_font, fill=(255,255,255,255))


	d.text((10,68), "Humidity:",font=medium_font, fill=(255,255,255,255))
	d.text((120,68), humidity,font=medium_font, fill=(255,255,255,255))
	#img.show()
	img.save("output/temp_hum.png") 

def windImage(data):
	large_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 60)
	medium_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 14)

	#tempreture= data["Tempreture"]
	#humidity= data["Humidity"]
	wind_speed= data["Wind_speed"]
	wind_direction= data["Wind_direction"]


	img = PIL.Image.new(mode ="RGBA", size = (197, 111),color=(0,0,0))
	
	
	d = ImageDraw.Draw(img)

	d.text((2,2), "Cantonment Board Varanasi",font=medium_font, fill=(255,255,255,255))
	d.text((12,15), "Air Quality Parameters",font=medium_font, fill=(255,255,255,255))
	
	d.text((10,48), "Wind Speed:",font=medium_font, fill=(255,255,255,255))
	d.text((100,48), wind_speed, font=medium_font,fill=(255,255,255,255))

	d.text((10,65), "Wind",font=medium_font, fill=(255,255,255,255))
	d.text((10,80), "Direction :",font=medium_font, fill=(255,255,255,255))
	d.text((100,80), wind_direction,font=medium_font, fill=(255,255,255,255))

	#img.show()
	img.save("output/wind_speed_dir.png") 

#used for display time only
def gentime():
	large_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 60)
	medium_font = ImageFont.truetype("fonts/Univers_65_Bold.ttf", 14)
	#base = Image.open('/home/pi/Desktop/main/background/background.jpg').convert('RGBA')

	# make a blank image for the text, initialized to transparent text color
	#txt = Image.new('RGBA', base.size, (255,255,255,0))
	img = PIL.Image.new(mode ="RGBA", size = (197, 111))
	# get a font
	#fnt = ImageFont.load("arial.pil")
	# get a drawing context
	
	d = ImageDraw.Draw(img)
	d.text((2,5), current_time,font=large_font, fill=(255,255,255,255))

	img.show()
	img.save("data/output/time.png") 
#gentime()

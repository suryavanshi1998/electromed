import subprocess
import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library
import time
import os

GPIO.setwarnings(False)    # Ignore warning for now
GPIO.setmode(GPIO.BCM)    # Use physical pin numbering
GPIO.setup(17,GPIO.OUT)
GPIO.setup(22,GPIO.OUT)
GPIO.setup(27,GPIO.OUT)
GPIO.output(27,GPIO.HIGH)


def connect():
		response = os.system("ping -c 1 " + "google.com")
		if response == 0:

	    	
			GPIO.output(17,GPIO.HIGH)
			GPIO.output(22,GPIO.HIGH)
		else:
			GPIO.output(17,GPIO.LOW)
			GPIO.output(22,GPIO.LOW)
		pass

connect()
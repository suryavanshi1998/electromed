# Python program to explain shutil.copyfile() method 
	
# importing os module 

import os 

# importing shutil module 
import shutil 
def copyfile():


	path = '/home/osmc/Movies/buffer'
		
	# Check whether the specified 
	# path exists or not 
	isExist = os.path.exists(path) 
	#print(isExist) 
		
		
	# Specify path 
	path = 'home/osmc/Movies/buffer/flag.py'
		
	# Check whether the specified 
	# path exists or not 
	isFile = os.path.isfile(path)
	print(isFile) 
	if isFile == True:

		source = "/var/lib/connman/wifi_b827ebe840e3_656d6564403137766e70757269_managed_psk"

		# Destination path 
		destination = "/home/osmc/Movies/"
		dest = shutil.copyfile(source, destination) 
		
copyfile()

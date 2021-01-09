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

		source = "/home/osmc/Movies/buffer/a.mp4"

		# Destination path 
		destination = "/home/osmc/Movies/a.mp4"
		dest = shutil.copyfile(source, destination) 
		
copyfile()

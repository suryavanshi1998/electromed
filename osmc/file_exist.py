# Python program to explain os.path.exists() method 
	
# importing os module 
import os 
	
# Specify path 
path = 'E:/Electro-Med/osmc'
	
# Check whether the specified 
# path exists or not 
isExist = os.path.exists(path) 
#print(isExist) 
	
	
# Specify path 
path = 'E:/Electro-Med/osmc/autoexec.py'
	
# Check whether the specified 
# path exists or not 
isFile = os.path.isfile(path)
#print(isFile) 
if isFile == True:
	#print("coppying files")


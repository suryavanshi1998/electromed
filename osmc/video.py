import xbmc
import time
import os
import logging
import shutil 
import zipfile

def autoexec():
			
	logging.basicConfig(filename='/home/osmc/.kodi/temp/Python.log', level=logging.DEBUG)
	logging.debug('This message should go to the log file')


	xbmc.executebuiltin( "PlayMedia(/home/osmc/.kodi/userdata/playlists/video/play2.m3u)"  )
	xbmc.executebuiltin("PlayerControl(play)")
	#time.sleep(50)
	
	xbmc.executebuiltin( "PlayerControl(repeatall)" )

	#print("coppying files")
	while(1):
		#time.sleep(10)
		
		#logging.debug('while loop')
		flag = 'home/osmc/Movies/buffer/flag.py'
		Zip = 'home/osmc/Movies/buffer/files.zip'
		isFile = os.path.isfile(flag)
		print(isFile)

		if isFile == True:
			os.remove(flag)
			folder = '/home/osmc/Movies/files'
			for filename in os.listdir(folder):
   				file_path = os.path.join(folder, filename)
   		 		try:
        			 if os.path.isfile(file_path) or os.path.islink(file_path):
           			    os.unlink(file_path)
        			 elif os.path.isdir(file_path):
           			    shutil.rmtree(file_path)
   				except Exception as e:
        					logging.debug('Failed to delete %s. Reason: %s' % (file_path, e))

			#file_name = "/home/osmc/Movies/buffer/files.zip"
			with zipfile.ZipFile("/home/osmc/Movies/buffer/files.zip", 'r') as zip_ref:
				zip_ref.extractall("/home/osmc/Movies/")
			logging.debug('extraceted successfully')

			source = "/home/osmc/Movies/files/play2.m3u"
			destination = "/home/osmc/.kodi/userdata/playlists/video/play2.m3u"
   			dest = shutil.copyfile(source, destination)
			logging.debug('file copied successfully') 
			
			xbmc.executebuiltin( "PlayerControl(stop)" )
			logging.debug('player closed')
			time.sleep(40)
			xbmc.executescript("/home/osmc/.kodi/userdata/autoexec.py")
			#os.remove(Zip)
			break



autoexec()
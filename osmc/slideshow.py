def autoexec():

	import xbmc
	import time
	#import sys
	xbmc.executebuiltin( "SlideShow(home/osmc/Pictures)" )
	time.sleep(20)
	xbmc.executebuiltin("action[Stop,10002")
	#sys.exit()
	#xbmc.executebuiltin( "PlayMedia(/home/osmc/.kodi/userdata/playlists/video/play2.m3u)"  )
	#xbmc.executebuiltin("PlayerControl(play)")
	#xbmc.executebuiltin( "PlayerControl(repeatall)" )
autoexec()
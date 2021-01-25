


import os
#hostname = "google.com" #example
response = os.system("ping -c 1 " + "google.com")

#and then check the response...
if response == 0:
  print ("is up!")
else:
  print ("is down!")
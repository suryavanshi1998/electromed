#!/bin/sh
# launcher.sh
# navigate to home directory, then to this directory, then execute python script, then back home

cd /
cd /home/osmc/.kodi/addons/service.autoexec
sudo python autoexec.py
cd /

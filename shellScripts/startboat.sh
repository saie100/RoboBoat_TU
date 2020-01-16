#!/bin/bash

#start ROSCORE
gnome-terminal --tab -e "bash -c 'roscore; bash'"

#wait for the roscore to finish initializing
sleep 5

#start up the rosbridge server
gnome-terminal --tab -e "bash -c 'roslaunch rosbridge_server rosbridge_websocket.launch; bash'"
#start up the serial arduino
gnome-terminal --tab -e "bash -c 'rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0; bash'"

gnome-terminal --tab -e "bash -c 'cd /home/ubuntu/RoboBoat_TU/boatControlWebsite; python -m SimpleHTTPServer; bash'"


#navigate to the directory with the html webpage
#gnome-terminal --tab
#cd /home/pi/catkin_ws/src/boat_gui/gui
#start the http server so the website can be accessed
#python -m SimpleHTTPServer

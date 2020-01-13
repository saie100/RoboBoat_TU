#!/bin/bash

#start ROSCORE
mate-terminal --tab -e "bash -c 'roscore; bash'"

#wait for the roscore to finish initializing
sleep 5

#start up the rosbridge server
mate-terminal --tab -e "bash -c 'roslaunch rosbridge_server rosbridge_websocket.launch; bash'"
#start up the serial arduino
mate-terminal --tab -e "bash -c 'rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0; bash'"

#mate-terminal --tab -e "bash -c 'cd /home/pi/catkin_ws/src/boat_gui/gui; python -m SimpleHTTPServer; bash'"


#navigate to the directory with the html webpage
#gnome-terminal --tab
#cd /home/pi/catkin_ws/src/boat_gui/gui
#start the http server so the website can be accessed
#python -m SimpleHTTPServer

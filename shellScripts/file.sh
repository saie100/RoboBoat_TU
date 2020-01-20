#!/bin/bash
gnome-terminal  --window --command="bash -c 'roscore; bash'" \
		--tab --command="bash -c 'sleep 5; roslaunch rosbridge_server rosbridge_websocket.launch; bash'" \
		--tab --command="bash -c 'sleep 5; rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0; bash'" \
		--tab --command="bash -c 'cd /home/ubuntu/RoboBoat_TU/boatControlWebsite; python -m SimpleHTTPServer; bash'" 

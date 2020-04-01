#!/bin/bash
gnome-terminal  --window --command="bash -c 'roscore; bash'" \
		--tab --command="bash -c 'sleep 5; roslaunch rosbridge_server rosbridge_websocket.launch; bash'" \
		--tab --command="bash -c 'sleep 5; source ~/catkin_ws/devel/setup.bash; rosrun roboboat_rosserial teensy_serial_node.py; bash'" \
		--tab --command="bash -c 'cd /home/ubuntu/RoboBoat_TU/Boat_Website; python -m SimpleHTTPServer; bash'" \
		--tab --command="bash -c 'sleep 7; ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-zed.sh;'" \
		--tab --command="bash -c 'sleep 7; ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-web_video_server.sh;'" \
		--tab --command="bash -c 'sleep 7; ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-rosserial_battery.sh;'"


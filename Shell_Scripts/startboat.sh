#!/bin/bash
gnome-terminal  --window --command="bash -c 'roscore; bash'" \
		--tab --command="bash -c 'sleep 5; ./start-rosbridge.sh; bash'" \
		--tab --command="bash -c 'sleep 5; ./start-rosserial_teensy.sh; bash'" \
		--tab --command="bash -c 'sleep 5; ./start-status_light_ctl.sh; bash'" \
		--tab --command="bash -c ' ./start-website.sh; bash'" \
		--tab --command="bash -c 'sleep 7; ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-zed.sh;'" \
		--tab --command="bash -c 'sleep 7; ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-web_video_server.sh;'" \
		--tab --command="bash -c 'sleep 7; ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-rplidar.sh;'" \
		--tab --command="bash -c 'sleep 7; ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-rosserial_battery.sh;'"


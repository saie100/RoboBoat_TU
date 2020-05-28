#!/bin/bash
roscore > /dev/null 2>&1 &
./start-website.sh > /dev/null 2>&1 &
(sleep 5 &&(
		./start-rosbridge.sh > /dev/null 2>&1 &
		./start-rosserial_teensy.sh > /dev/null 2>&1 &
		./start-control_status.sh > /dev/null 2>&1 &
	    )
) &
(sleep 7 && (
		ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-rosserial_battery.sh > /dev/null 2>&1 &
		ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-zed.sh > /dev/null 2>&1 &
		ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-web_video_server.sh > /dev/null 2>&1 &
		ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-rplidar.sh > /dev/null 2>&1 &
	    )
) &
read -p "Press [Enter] to stop the boat...";
./killboat.sh;

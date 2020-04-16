#!/bin/bash
export ROS_MASTER_URI=http://10.19.122.101:11311/;
cd /home/ubuntu/RoboBoat_TU/Boat_Website; 
python -m SimpleHTTPServer;

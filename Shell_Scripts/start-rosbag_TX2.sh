#!/bin/bash
#export ROS_IP=0.0.0.0;
export ROS_MASTER_URI=http://10.19.122.101:11311/;
source ~/catkin_ws/devel/setup.bash;
cd ~/rosbag_files && touch test.txt;

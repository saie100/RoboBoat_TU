#!/bin/bash
#export ROS_IP=0.0.0.0;
export ROS_MASTER_URI=http://10.19.122.101:11311/;
source ~/catkin_ws/devel/setup.bash;
cd ~/rosbag_files && rosbag record -O subset /BatteryVoltage /ControlMode /IMU_absoluteOrientation /IMU_angularVelocity /IMU_eulerOrientation /IMU_linearAcceleration /IMU_magVec /Motor_leftPWM /Motor_rightPWM /gps /zed/zed_node/stereo_raw/image_raw_color /zed/zed_node/depth/depth_registered /scan && sleep 5;

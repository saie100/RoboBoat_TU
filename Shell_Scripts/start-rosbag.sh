#!/bin/bash
ssh -t ubuntu@10.19.122.102 bash -c ./RoboBoat_TU/Shell_Scripts/start-rosbag_TX2.sh > /dev/null 2>&1 &

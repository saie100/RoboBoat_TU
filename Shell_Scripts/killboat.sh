#!/bin/bash

pkill -f SimpleHTTPServer
pkill -f rosbridge
pkill -f rosserial
pkill -f roscore
ssh -t ubuntu@10.19.122.102 "pkill -f zed"
ssh -t ubuntu@10.19.122.102 "pkill -f web_video_server"
ssh -t ubuntu@10.19.122.102 "pkill -f rosserial"
ssh -t ubuntu@10.19.122.102 "pkill -f rplidar"

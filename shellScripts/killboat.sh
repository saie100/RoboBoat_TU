#!/bin/bash

echo $(ps -ef | grep ros | grep -v grep | awk '{print $2}')
echo $(ps -ef | grep SimpleHTTPServer | grep -v grep | awk '{print $2}')

#ps -ef | grep SimpleHTTPServer | grep -v grep | awk '{print $2}' | xargs kill


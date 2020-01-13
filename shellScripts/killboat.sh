#!/bin/bash

ps -ef | grep ros | grep -v grep | awk '{print $2}' | xargs kill

ps -ef | grep SimpleHTTPServer | grep -v grep | awk '{print $2}' | xargs kill


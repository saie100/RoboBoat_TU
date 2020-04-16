#!/usr/bin/python3

#import the GPIO and time package
import RPi.GPIO as GPIO
import time
from time import sleep 
import os
import subprocess

LED_red = 11 # GPIO 17
LED_green = 13 # GPIO 27
LED_blue = 15 # GPIO 22

LED_red = 17 # GPIO 17
LED_green = 27 # GPIO 27
LED_blue = 22 # GPIO 22

RGB = [LED_red, LED_green, LED_blue]

BUTTON_Power = 29 # GPIO 5
BUTTON_ROS = 31 # GPIO 6

BUTTON_Power = 5 # GPIO 5
BUTTON_ROS = 6 # GPIO 6

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(LED_red, GPIO.OUT)
GPIO.setup(LED_green, GPIO.OUT)
GPIO.setup(LED_blue, GPIO.OUT)

GPIO.setup(BUTTON_Power, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(BUTTON_ROS, GPIO.IN, pull_up_down=GPIO.PUD_UP)

GPIO.output(RGB, [False, False, True]) # Display BLUE on the LED

def Power_Pressed(channel):
	# GPIO.output([LED_blue, LED_green, LED_blue] ,false)
	GPIO.remove_event_detect(channel)
	channel = GPIO.wait_for_edge(channel, GPIO.RISING, timeout=5000)
	
	if channel is None: # If the button is held down for more than 5 seconds
		print('SHUTDOWN')
		GPIO.output(RGB, [True, False, False]) # Display RED on the LED
		sleep(5)
		os.system("shutdown -h now") # Shutdown the computer
		
	else:
		print('RESET') # If the button is held down for less than 5 seconds
		GPIO.output(RGB, [True, True, False]) # Display YELLOW on the LED
		sleep(5)
		os.system("shutdown -r now") # Restart the computer
	GPIO.remove_event_detect(BUTTON_Power)
	GPIO.add_event_detect(BUTTON_Power, GPIO.FALLING, callback=Power_Pressed)

def ROS_Pressed(channel):
	GPIO.output(RGB, [False, False, True]) # Display BLUE on the LED
	#os.system("./killboat.sh") # Stop all boat processes
	subprocess.call("./home/ubuntu/RoboBoat_TU/Shell_Scripts/killboat.sh")
	sleep(1)
	subprocess.call("./home/ubuntu/RoboBoat_TU/Shell_Scripts/start-noGUI.sh", shell=True)
	GPIO.output(RGB, [False, True, False]) # Display GREEN on the LED


GPIO.add_event_detect(BUTTON_Power, GPIO.FALLING, callback=Power_Pressed)
GPIO.add_event_detect(BUTTON_ROS, GPIO.FALLING ,callback=ROS_Pressed)

# GPIO.add_event_callback(BUTTON_Power, Power_Pressed)
# GPIO.add_event_callback(BUTTON_ROS, ROS_Pressed)

while True:
    # Put anything you want to loop normally in here
    sleep(3600);  

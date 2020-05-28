#!/usr/bin/env python

# Import the generic ROS library
import rospy
# Import the std_msgs/Int32 message type for the status light & control mode selection 
from std_msgs.msg import Int32

# Import the functions for interacting the the Raspberry Pi GPIO
import RPi.GPIO as GPIO

# Broadcom SOC channel connected to the manual/autonomous status light select wire
LED_GPIO = 2
# When written to the LED_GPIO channel, this turns on the Amber status light 
# and turns off the Blue status light
AMBER_LIGHT_ON = True
# When written to the LED_GPIO channel, this turns on the Blue status light 
# and turns off the Amber status light
BLUE_LIGHT_ON = False


def manualControl():
	# Add code to STOP autonomous stuff here

	GPIO.output(LED_GPIO, AMBER_LIGHT_ON)
	return "Manual Control"

def navigationChannel():
	# Add code to start autonomous stuff here

	GPIO.output(LED_GPIO, BLUE_LIGHT_ON)
	return "Mandatory Navigation Channel"

def speedGate():
	# Add code to start autonomous stuff here

	GPIO.output(LED_GPIO, BLUE_LIGHT_ON)
	return "Speed Gate"

def windingNavigationChannel():
	# Add code to start autonomous stuff here

	GPIO.output(LED_GPIO, BLUE_LIGHT_ON)
	return "Winding Navigation Channel With Obstacles"

def obstacleField():
	# Add code to start autonomous stuff here

	GPIO.output(LED_GPIO, BLUE_LIGHT_ON)
	return "Obstacle Field with Circumnavigation"

def acousticDocking():
	# Add code to start autonomous stuff here

	GPIO.output(LED_GPIO, BLUE_LIGHT_ON)
	return "Acoustic Docking"

def packageDelivery():
	# Add code to start autonomous stuff here

	GPIO.output(LED_GPIO, BLUE_LIGHT_ON)
	return "Package Delivery"


# The controlModeHandler function will call the correct handler function depending
# on the value recieved on the '/ControlMode' topic
def controlModeHandler(controlMode):
	switcher={
		0: manualControl,
		1: navigationChannel,
		2: speedGate, 
		3: windingNavigationChannel,
		4: obstacleField, 
		5: acousticDocking, 
		6: packageDelivery
	}
	func=switcher.get(controlMode,lambda :'Invalid')
	return func()


# The control_state_callback function will execute whenever a new message is published to
# the '/ControlMode' topic
def control_state_callback(msg):
	handlerRet = controlModeHandler(msg.data)
	print("Course: %-45s (ControlMode Data: %d)" %(handlerRet,msg.data))

if __name__ == '__main__':

	print "Custom Python Node: control_selector\n"

	# Configure the Raspberry Pi GPIO 
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(LED_GPIO, GPIO.OUT)
	GPIO.output(LED_GPIO, AMBER_LIGHT_ON)

	# Create a new ROS node with the name 'control_selector'
	rospy.init_node('control_selector')
	# Subscribe to the '/ControlMode' ROS Topic to receive control and status light information
	# and define the callback function for the subscriber
	rospy.Subscriber('ControlMode', Int32, control_state_callback)
	# Wait for new messages
	rospy.spin()

	# Clean up the GPIO when exiting
	GPIO.cleanup()




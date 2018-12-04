#!/usr/bin/env python
import serial
import rospy
import time
from std_msgs.msg import String, Int32
from sensor_msgs.msg import Range

############## Methods #############

def RepresentsFloat(s):
    try: 
        float(s)
        return True
    except ValueError:
        return False

####################################


# To which topic on Willy we will publish
pubTopicName = 'sonar_data'
subTopicName = 'sonar_command'

# Init ROS components
rospy.init_node('sonar')
pubTopicInstance = rospy.Publisher(pubTopicName, Range ,queue_size=25)

# Init default values
topicMessage = ""

# Init serial components
socket = serial.Serial()
socket.baudrate = 9600
socket.port = '/dev/ttyACM0'
socket.timeout = 1
socket.open()

# Continous loop for publishing serial data
while not rospy.is_shutdown(): 
    topicMessage = socket.readline()
    topicMessage = topicMessage.rstrip()

    message = Range()
    if(RepresentsFloat(topicMessage)):
	message.header.stamp.secs = rospy.get_rostime().secs
	message.header.stamp.nsecs = rospy.get_rostime().nsecs
	message.header.frame_id = "/us_ranger"
	message.radiation_type = 0
	message.field_of_view = 0.01
	message.max_range = 5
	message.min_range = 0.1
	message.range = float(topicMessage) / 100
	pubTopicInstance.publish(message)
	print(message)
    print(topicMessage)


	


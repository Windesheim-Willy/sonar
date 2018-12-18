#!/usr/bin/env python
import serial
import rospy
import time
from std_msgs.msg import String, Int32
from sensor_msgs.msg import Range
import re

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
topicMessage = tuple()
TopicDistance = tuple()

# Init serial components
socket = serial.Serial()
socket.baudrate = 9600
socket.port = '/dev/willy_sonar'
socket.timeout = 1
socket.open()


# Function for publish on topic
def PostOnTopic(frameid, Distance):
 
    message = Range()
    if(RepresentsFloat(Distance)):
	message.header.stamp.secs = rospy.get_rostime().secs
	message.header.stamp.nsecs = rospy.get_rostime().nsecs
	message.header.frame_id = frameid
	message.radiation_type = 0
	message.field_of_view = 0.01
	message.max_range = 5
	message.min_range = 0.1
	message.range = float(Distance) / 100
	pubTopicInstance.publish(message)
	print(message)
        print(Distance)


# Continous loop for publishing serial data
while not rospy.is_shutdown(): 
    if re.match(r"/d+\|\d+\|\d+", topicMessage)

        topicMessage = socket.readline()
        topicMessage = topicMessage.rstrip()
    
        print(topicMessage)
        PostOnTopic("/front",float(topicMessage.split("|")[0]))
        PostOnTopic("/backRight",float(topicMessage.split("|")[1]))
        PostOnTopic("/backLeft",float(topicMessage.split("|")[2]))

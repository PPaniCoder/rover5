import logging
import roslib; roslib.load_manifest('rover5')
import rospy
import sys
from rover5.msg import *
from std_msgs.msg import String

drivingPub = None

def setup():
	try:
		global drivingPub
		drivingPub = rospy.Publisher('rover5_move_msg', moveRover5, queue_size=10)
		rospy.init_node('rover5_publisher')
		print "setup rosDriving"
	except rospy.ServiceException, e:
		print "Service call failed: %s"% e
	

def changeDirection(direction):
	logging.debug('changeDirection: %s' % direction)
	#add_two_ints_client(4, 5)
	#sendEcho()
	directionKey = 0
	if "left" == direction:
		directionKey = 106
	elif "right" == direction:
		directionKey =108
	elif "forward" == direction:
		directionKey = 105
	elif "back" == direction:
		directionKey = 107
	elif "up" == direction:
		directionKey = 46
	elif "down" == direction:
		directionKey = 44
	elif "boost" == direction:
		directionKey = 7
	elif "stop" == direction:
		directionKey = 113

	sendMsgDriving(directionKey, 0)
	return

def sendMsgDriving(direction, velocity):
	try:
		msg = moveRover5()
		msg.direction = direction;
		drivingPub.publish(msg)
		logging.debug('success send direction=%c' % direction)
	except rospy.ServiceException, e:
		print "Service call failed: %s"% e
	return

def sendEcho():
	try:
		drivingPub.publish("hello echo")
		logging.debug('success send')
	except rospy.ServiceException, e:
		print "Service call failed: %s"% e
	return

if __name__ == "__main__":
	logging.basicConfig(level=logging.DEBUG)
	setup()
	changeDirection('forward')


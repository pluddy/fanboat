#!/usr/bin/env python

import rospy
from project.msg import rocket_msg
from lab3.msg import ballLandInfo
from project.msg import angle
from fanboat_ll.msg import fanboatMotors
from fanboat_ll.msg import fanboatLL
from lab3.msg import hasBall

class rocket_ship(object):
	rocketPub = None
  	anglePub = None
	defenseState = 0
	TURNING_ANGLE = -6.0
	OTHER_TURNING_ANGLE = 6.0
	CC_FAST = -25.0
	OTHER_FAST = 25.0
	lastDistance = 1000.0
	lastX = 1000.0
	lastY = 1000.0
	go = 0
	done = 0
	targetYaw = 1000.0
	timesFired = 0
	nextFired = 1
	state = 0
	fastCount = 0
	CCdirection = 0
	fll = fanboatLL()
	left = -1000
	right = -1000

	#launcher = armageddon.Armageddon()
	def __init__(self):
		rospy.init_node('rocket_ship')

	def init_subcribers(self):
		print "init subs"
		rospy.Subscriber('/ballLandInfo', ballLandInfo, self.camCallback)
		rospy.Subscriber('/sensors', fanboatLL, self.imuCallback)
		rospy.Subscriber('/launcher_topic', rocket_msg, self.launcherCallback)
			
	def init_publishers(self):
		print "init pubs"
		self.rocketPub = rospy.Publisher('ship_topic', rocket_msg, queue_size=1)
		self.anglePub = rospy.Publisher('angle', angle, queue_size=1)
	savedYaw = None
	distance = 10000
	def camCallback(self, ballLandInfo):
		#print 'cam callback'
		t = ballLandInfo.type
		lid = ballLandInfo.id
		dist = ballLandInfo.distance
		x = ballLandInfo.x
		y = ballLandInfo.y
			
	def imuCallback(self, fanboatLL):
		self.fll = fanboatLL
		self.left = fanboatLL.a1
		self.right = fanboatLL.a0
			
		ang = angle()
		print 'defense state ', self.defenseState
		if self.defenseState == 2:
			#just got in defense mode, turn left and wait.
			print 'defense state 2, yaw = ', self.fll.yaw
			ang.angle = -90.0 # + self.fll.yaw
			self.savedYaw = -90.0
			if self.fll.yaw < -85.0 and self.fll.yaw > -95.0:
				self.defenseState = 3
		
		elif self.defenseState == 3:
			#this is for going to the left landmark
			if self.savedYaw is 90.0 and self.fll.yaw < 95.0 and self.fll.yaw > 85.0:
				ang.forward = 1
				self.savedYaw = None
			elif self.savedYaw == -90.0 and self.fll.yaw > -95.0 and self.fll.yaw < -85.0:
				ang.forward = 1
				self.savedYaw = None
			elif self.left > 200 or self.right > 200:
				if self.savedYaw is None:
					if self.fll.yaw < 0:
						self.savedYaw = 90.0
					else:
						self.savedYaw = -90.0
			
				ang.angle = self.savedYaw
			elif self.savedYaw is None:
				ang.forward = 1
			else:
				ang.angle = self.savedYaw
		elif self.defenseState == 4:
			ang.angle = 0.0
			ang.forward = 0
				
		self.anglePub.publish(ang)
			
	def launcherCallback(self, rocket_msg1):
		self.defenseState = rocket_msg1.state
		self.timesFired = rocket_msg1.timesFired
		rocketMsg = rocket_msg()
		rocketMsg.state = self.defenseState
		rocketMsg.timesFired = self.timesFired
		self.rocketPub.publish(rocketMsg)

	def main_loop(self):
		self.init_publishers()
		self.init_subcribers()
		rate = rospy.Rate(10);
		while not rospy.is_shutdown():
			rate.sleep()

if __name__ == '__main__':
	try:
		#print "main"
		rocket = rocket_ship()
		rocket.main_loop()

	except rospy.ROSInterruptException:
		pass

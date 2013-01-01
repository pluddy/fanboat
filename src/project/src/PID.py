#!/usr/bin/env python

import rospy
from project.msg import angle
from fanboat_ll.msg import fanboatLL
from fanboat_ll.msg import fanboatMotors

class PID(object):

	fll = fanboatLL()
	forwardL = 0.8
	forwardR = 0.74
	prevDiff = 0
	errorYaw = 0
	
	p = 0.2
	d = 1.0
	leftScale = 1.0
	rightScale = 1.0
	
	def __init__(self):
		rospy.init_node('PID')

	def init_subcribers(self):
		print "init subs"
		rospy.Subscriber('/sensors', fanboatLL, self.sensor_callback)
		rospy.Subscriber('/angle', angle, self.angle_callback)
	def init_publishers(self):
		self.motors = rospy.Publisher('motors', fanboatMotors, queue_size=1)

	def sensor_callback(self, f_ll):
		self.fll = f_ll

	def angle_callback(self, ang):
		boat = fanboatMotors()
		boat.left = 0.2 * self.leftScale
		boat.right = 0.2 * self.rightScale
		self.errorYaw = self.errorYaw + 0.04
		
		if ang.forward ==1:
			boat.left = self.forwardL * self.leftScale
			boat.right = self.forwardR * self.rightScale
		else:
			diff = ang.angle - (self.fll.yaw + self.errorYaw)
			if diff > 180:
				diff = diff - 360
			elif diff < -180:
				diff = diff + 360
			
			error = diff - self.prevDiff
			self.prevDiff = diff
			
			dFactor = self.d * error
			pFactor = self.p * diff
			
			if diff > 0:
				boat.left = (pFactor + dFactor) * self.leftScale
				if boat.left > 1.0:
					boat.left = 1.0
				boat.left = self.map(boat.left, 0.0, 1.0, 0.6, 1.0)
				
			else:
				boat.right = -(pFactor + dFactor) * self.rightScale
				if boat.right > 1.0:
					boat.right = 1.0
				boat.right = self.map(boat.right, 0.0, 1.0, 0.6, 1.0)
				
		print 'left ', boat.left, 'right ', boat.right
		self.motors.publish(boat)
		
	def map(self, x, in_min, in_max, out_min, out_max):
		if x < in_min:
			x = in_min
		elif x > in_max:
			x = in_max
			
		x = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

		if x < out_min:
			x = out_min
		elif x > out_max:
			x = out_max
			
		return x

	def main_loop(self):
		self.init_publishers()
		#print "loop"
		self.init_subcribers()
		#self.init_params

		while not rospy.is_shutdown():
			i = 1


if __name__ == '__main__':
	try:
		print "main"
		pid = PID()
		#print "rocket node"
		pid.main_loop()

	except rospy.ROSInterruptException:
		pass

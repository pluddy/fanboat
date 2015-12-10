#!/usr/bin/env python
import rospy
import os

class run_cmd(object):

	def main_loop(self):
		print 'start lsusb command'
		sudoPassword = rospy.get_param('~password', 'robotics')
		print sudoPassword
		command = 'lsusb -v 2>&1 1>/dev/null'

		os.system('echo '+sudoPassword+' | sudo -S '+command)

		print 'lsusb command done'

	def __init__(self):
		rospy.init_node('ROS Python Command Line')

if __name__ == '__main__':
	cmd = run_cmd()
	cmd.main_loop()

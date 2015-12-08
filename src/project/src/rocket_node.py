#!/usr/bin/env python

import rospy
import armageddon
from project.msg import rocket_msg
from lab3.msg import ballLandInfo

class rocket_node(object):
    #publisher1 = None
    #publisher2 = None
    subscriber1 = None
    subscriber2 = None

    #launcher = armageddon.Armageddon()
    def __init__(self):
        rospy.init_node('rocket_node')

    def init_subcribers(self):
        print "init subs"
        rospy.Subscriber('/rocket_command', rocket_msg, self.rocket_callback)
        rospy.Subscriber('/ballLandInfo', ballLandInfo, self.camCallback)
    #def init_publishers(self):
        #self.publisher1 = rospy.Publisher('rocket_topic',)

    def calculateTurnage(self, angle):
        rocket = armageddon.Armageddon()
        if angle > 0:
            rocket.RIGHT(1000)
        else:
            rocket.LEFT(1000)

    def rocket_callback(self, rocket_msg):
        print 'msg\n'

    def camCallback(self, ballLandInfo):
        print 'cam callback'
        x = ballLandInfo.x
        y = ballLandInfo.y
        t = ballLandInfo.type
        d = ballLandInfo.distance
        angle = x/300.0*22.5
        angle = angle * -1.0
        self.calculateTurnage(angle)


    def main_loop(self):
        #self.init_publishers
        #print "loop"
        self.init_subcribers()
        #self.init_params
        rate = rospy.Rate(10);

        while not rospy.is_shutdown():
            #put code here
            #print "while loop"
            rate.sleep()

if __name__ == '__main__':
    try:
        print "main"
        rocket = rocket_node()
        print "rocket node"
        rocket.main_loop()



    except rospy.ROSInterruptException:
        pass

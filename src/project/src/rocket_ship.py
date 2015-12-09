#!/usr/bin/env python

import rospy
from project.msg import rocket_msg
from lab3.msg import ballLandInfo
from lab2.msg import angle_msg
from fanboat_ll.msg import fanboatMotors
from fanboat_ll.msg import fanboatLL

class rocket_ship(object):
    rocketPub = None
    anglePub = None
    #subscriber1 = None
    #subscriber2 = None
    isOffence = 1
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

    #launcher = armageddon.Armageddon()
    def __init__(self):
        rospy.init_node('rocket_ship')

    def init_subcribers(self):
        print "init subs"
        rospy.Subscriber('/ballLandInfo', ballLandInfo, self.camCallback)
        rospy.Subscriber('/fanboatLL', fanboatLL, self.imuCallback)
        rospy.Subscriber('/launcher_topic', rocket_msg, self.launcherCallback)
        rospy.Subscriber

    def init_publishers(self):
        print "init pubs"
        self.rocketPub = rospy.Publisher('ship_topic', rocket_msg, queue_size=1)
        self.anglePub = rospy.Publisher('angle_topic', angle_msg, queue_size=1)

    def camCallback(self, ballLandInfo):
        print 'cam callback'
        t = ballLandInfo.type
        if t == 0 and self.isOffence == 0:
            angle = angle_msg()
            angle.angle = self.TURNING_ANGLE

    def launcherCallback(self, rocket_msg):
        self.isOffence = rocket_msg.rocket
        if self.isOffence == 1:
            print 'launcher is offensive'
        else:
            print 'deffensive mode'
        self.timesFired = rocket_msg.timesFired

    def main_loop(self):
        self.init_publishers()
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

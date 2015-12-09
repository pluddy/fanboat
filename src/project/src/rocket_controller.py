#!/usr/bin/env python

import rospy
from project.msg import rocket_msg
from lab3.msg import ballLandInfo
from lab2.msg import angle_msg
from fanboat_ll.msg import fanboatMotors
from fanboat_ll.msg import fanboatLL

class rocket_controller(object):
    rocketPub = None
    anglePub = None
    #subscriber1 = None
    #subscriber2 = None

    #launcher = armageddon.Armageddon()
    def __init__(self):
        rospy.init_node('rocket_controller')

    def init_subcribers(self):
        print "init subs"
        #rospy.Subscriber('/rocket_command', rocket_msg, self.rocket_callback)
        rospy.Subscriber('/ballLandInfo', ballLandInfo, self.camCallback)

    def init_publishers(self):
        print "init pubs"
        self.rocketPub = rospy.Publisher('rocket_topic', rocket_msg, queue_size=1)
        self.anglePub = rospy.Publisher('angle_topic', angle_msg, queue_size=1)

    def calculateTurnage(self, angle):
        rocket = armageddon.Armageddon()
        if angle > 0:
            rocket.RIGHT(1000)
        else:
            rocket.LEFT(1000)

    def camCallback(self, ballLandInfo):
        print 'cam callback'
        x = ballLandInfo.x
        y = ballLandInfo.y
        t = ballLandInfo.type
        d = ballLandInfo.distance
        angle = x/300.0*22.5
        angle = angle * -1.0
        rocket = rocket_msg()
        rocket.angle = angle
        if angle < 10 and angle > -10:
            rocket.fire = 1
        else:
            rocket.fire = 0
        rocket.stop = 0
        self.rocketPub.publish(rocket)

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

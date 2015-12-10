#!/usr/bin/env python

import rospy
from project.msg import rocket_msg
from lab3.msg import ballLandInfo
from lab2.msg import angle_msg
from fanboat_ll.msg import fanboatMotors
from fanboat_ll.msg import fanboatLL
from lab3.msg import hasBall

class rocket_ship(object):
    rocketPub = None
    anglePub = None
    #subscriber1 = None
    #subscriber2 = None
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
        rospy.Subscriber('/fanboatLL', fanboatLL, self.imuCallback)
        rospy.Subscriber('/launcher_topic', rocket_msg, self.launcherCallback)
        rospy.Subscriber('/lrsensors', hasBall, self.rangeCallback)

	def init_publishers(self):
		print "init pubs"
		self.rocketPub = rospy.Publisher('ship_topic', rocket_msg, queue_size=1)
		self.anglePub = rospy.Publisher('angle_arb', angle_msg, queue_size=1)

    def rangeCallback(self, hasBall):
        self.left = hasBall.left
        self.right = hasBall.right

    distance = 10000;
    def camCallback(self, ballLandInfo):
        #print 'cam callback'
        t = ballLandInfo.type
        lid = ballLandInfo.id
        dist = ballLandInfo.distance
        x = ballLandInfo.x
        y = ballLandInfo.y
        angle = angle_msg()

        if self.defenseState == 2 and t == 0:
            #just got in defense mode, turn left and wait.
            angle.angle = -90.0 + self.fll.yaw
            angle.thrust = .3
            self.anglePub.publish(angle)
            i = 0
            while i < 5000:
                i = i+1

        elif self.defenseState == 3 and t == 0 and lid = 70:
            #this is for going to the left landmark
            if dist < 150 or self.left > 450 or self.right > 450:
                #if too close turn around and look for other landmark
                angle.angle = -175 + self.fll.yaw
                angle.thrust = .3
                self.anglePub.publish(angle)
                self.defenseState = 4
            else:
                #if not close enough get closer
                diffang = (x/300.0) * 22.5
                diffang = diffang + self.fll.yaw
                angle.angle = diffang
                angle.thrust = .3

        elif self.defenseState == 4 and t == 0 and lid = 200;
            #this is for going to the right landmark
            if dist < 150:
                #if too close turn around and look for other landmark
                angle.angle = -175 + self.fll.yaw
                angle.thrust = .3
                self.anglePub.publish(angle)
                self.defenseState = 3
            else:
                #if not close enough get closer
                diffang = (x/300.0) * 22.5
                diffang = diffang + self.fll.yaw
                angle.angle = diffang
                angle.thrust = .3

    def imuCallback(self, fanboatLL):
        fll = fanboatLL

    def launcherCallback(self, rocket_msg):
        self.defenseState = rocket_msg.state
        self.timesFired = rocket_msg.timesFired
        rocketMsg = rocket_msg()
        rocketMsg.state = self.defenseState
        rocketMsg.timesFired = self.timesFired
        rocketPub.publish(rocketMsg)

    def main_loop(self):
        self.init_publishers()
        self.init_subcribers()
        rate = rospy.Rate(10);
        while not rospy.is_shutdown():
            rate.sleep()

if __name__ == '__main__':
    try:
        print "main"
        rocket = rocket_ship()
        print "rocket node"
        rocket.main_loop()

    except rospy.ROSInterruptException:
        pass

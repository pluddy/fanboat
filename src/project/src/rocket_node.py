#!/usr/bin/env python

import rospy
import armageddon
from project.msg import rocket_msg
from lab3.msg import ballLandInfo



class rocket_node(object):
    rocketPub = None
    #publisher2 = None
    subscriber1 = None
    subscriber2 = None
    yawState = None
    pitchState = None
    fire = None
    timer = 0
    lost = 1
    timesFired = 0
    isoffense = 1
    lostCount = 0
    spinDirection = 1
    

    def __init__(self):
        rospy.init_node('rocket_node')

    def init_subcribers(self):
        print "init subs"
        rospy.Subscriber('/rocket_command', rocket_msg, self.rocket_callback)
        rospy.Subscriber('/ballLandInfo', ballLandInfo, self.camCallback)
    def init_publishers(self):
        self.rocketPub = rospy.Publisher('launcher_topic', rocket_msg, queue_size=1)

    def calculateTurnage(self, x, y, dist):
        if dist < 450 and dist > 0:
            self.lost = 0
            yaw = x/300.0*22.5

            if yaw > 2:
                self.yawState = 1
            elif yaw < -2:
                self.yawState = -1
            else:
                self.yawState = 0

            thresholdPixels = 30

            targetY = -dist / 4.2


            if y > targetY + thresholdPixels:
                self.pitchState = 1
            elif y < targetY - thresholdPixels:
                self.pitchState = -1
            else:
                self.pitchState = 0

            if self.yawState is 0 and self.pitchState is 0 and self.timer <= 0:
                self.fire = 1
            else:
                self.fire = 0

        else:
            self.lost = 1
            self.fire = 0
            self.pitchState = 0
            self.yawState = 0

    def rocket_callback(self, rocket_msg):
        self.isoffense = rocket_msg.state
        print ''+ self.isoffense + ' msg\n'

    def camCallback(self, ballLandInfo):
        x = ballLandInfo.x
        y = ballLandInfo.y
        t = ballLandInfo.type
        d = ballLandInfo.distance
        print x , ' ' , y
        self.calculateTurnage(x, y, d)

    def main_loop(self):
        self.init_publishers()
        #print "loop"
        self.init_subcribers()
        #self.init_params
        rate = rospy.Rate(10);
        rocket = armageddon.Armageddon()

        while not rospy.is_shutdown():
            if self.isoffense ==1:
                if self.timer > 0:
                    self.timer = self.timer - 1
                print self.timer

                if self.lost is 0:
                    self.lostCount = 0
                    if self.yawState is 0 and self.pitchState is 0:
                        rocket.STOP()
                        print "stop"
                    else:
                        print "yaw: ", self.yawState, "pitch: ", self.pitchState
                        if self.yawState is 1:
                            rocket.RIGHT(20.0)
                        elif self.yawState is -1:
                            rocket.LEFT(20.0)

                        if self.pitchState is 1:
                            rocket.UP(20.0)
                        elif self.pitchState is -1:
                            rocket.DOWN(20.0)

                    if self.fire is 1:
                        #rocket.STOP()
                        rocket.FIRE()

                        #rocket.FIRE()
                        #rocket.FIRE()
                        #rocket.FIRE()
                        #rocket.FIRE()
                        self.timer = 200
                        self.fire = 0
                        print "fire"
                        #i = 0
                       # while i < 20000:
                        #    i = i+1
                        #    print i
                        self.timesFired = self.timesFired +1
                        print ' '
                        print ' '
                        print self.timesFired
                        print ' '
                        print ' '
                        rocketmsg = rocket_msg()
                        rocketmsg.timesFired = self.timesFired
                        if self.timesFired >= 4:
                            self.isoffense = 0
                            rocketmsg.state = 0
                        else:
                            rocketmsg.state = 1
                        self.rocketPub.publish(rocketmsg)
                

                else: #lost
                    print "lost"
                    rocket.DOWN(100.0)                    
                    self.lostCount = self.lostCount + 1
                    if self.lostCount >= 60:
                        self.spinDirection = -self.spinDirection
                        self.lostCount = 0
                    
                    if self.spinDirection is 1:
                        rocket.RIGHT(100.0)
                    else:
                        rocket.LEFT(100.0)
                        
            else:
                print 'defense'
            
            rate.sleep()
            

if __name__ == '__main__':
    try:
        print "main"
        rocket = rocket_node()
        print "rocket node"
        rocket.main_loop()

    except rospy.ROSInterruptException:
        pass

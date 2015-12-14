#!/usr/bin/env python

import rospy
import armageddon
from time import sleep
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
    timesFired = -30
    defenseState = 0
    lostCount = 0
    spinDirection = 1


    def __init__(self):
        rospy.init_node('rocket_node')

    def init_subcribers(self):
        print "init subs"
        rospy.Subscriber('/ship_topic', rocket_msg, self.rocket_callback)
        rospy.Subscriber('/ballLandInfo', ballLandInfo, self.camCallback)
    def init_publishers(self):
        self.rocketPub = rospy.Publisher('launcher_topic', rocket_msg, queue_size=1)

    def calculateTurnage(self, x, y, dist):
        #print 'calculating turnage'
#        print dist
        if dist < 550 and dist > 0:

            self.lost = 0
            print self.lost
            yaw = x/300.0*22.5

            if yaw > 10:
                self.yawState = 3
            elif yaw < -10:
                self.yawState = -3
            elif yaw > 5:
                self.yawState = 2
            elif yaw < -5:
                self.yawState = -2
            elif yaw > 1 and self.timer > 0: #only get really accurate if time left
                self.yawState = 1
            elif yaw < -1 and self.timer > 0:
                self.yawState = -1
            else:
                self.yawState = 0
                
            thresholdPixels = 30

            targetY = (-dist / 4.2) - 10
            #print 'I see it!!'

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

    def rocket_callback(self, rocket_msg1):
        if rocket_msg1.state == 1:
            #print 'rocket callback in if'
            rocketMsg = rocket_msg()
            rocketMsg.state = 2
            rocketMsg.timesFired = 4
            self.rocketPub.publish(rocketMsg)
        

    def camCallback(self, ballLandInfo):
#        print 'calc turn'
        x = ballLandInfo.x
        y = ballLandInfo.y
        t = ballLandInfo.type
        d = ballLandInfo.distance
        #print x , ' ' , y
        self.calculateTurnage(x, y, d)

    def main_loop(self):
        self.init_publishers()
        #print "loop"
        self.init_subcribers()
        #self.init_params
        rate = rospy.Rate(10);
        self.rocket = armageddon.Armageddon()

        while not rospy.is_shutdown():
            #print 'defense state = ', self.defenseState
            if self.defenseState == 0:
                if self.timer > 0:
                    self.timer = self.timer - 1
                #print self.timer
                #print 'lost ', self.lost
                #print 'yaw ', self.yawState
                #print 'pitch ', self.pitchState
                #print 'timesFired ', self.timesFired


                if self.lost is 0:
                    self.lostCount = 0
                    if self.yawState is 0 and self.pitchState is 0:
                        self.rocket.STOP()
                        print "stop"
                    else:
                        #print "yaw: ", self.yawState, "pitch: ", self.pitchState
                        if self.yawState is 1:
                            self.rocket.RIGHT(10.0)
                        elif self.yawState is -1:
                            self.rocket.LEFT(10.0)
                        elif self.yawState is 2:
                            self.rocket.RIGHT(20.0)
                        elif self.yawState is -2:
                            self.rocket.LEFT(20.0)
                        elif self.yawState is 3:
                            self.rocket.RIGHT(40.0)
                        elif self.yawState is -3:
                            self.rocket.LEFT(40.0)

                        if self.pitchState is 1:
                            self.rocket.UP(20.0)
                        elif self.pitchState is -1:
                            self.rocket.DOWN(20.0)

                    if self.fire is 1:
                        self.rocket.FIRE()
                        self.timer = 100
                        self.fire = 0
                        #print "fire"
                        self.timesFired = self.timesFired +1
                        #print '\n\n', self.timesFired, '\n\n'
                        rocketmsg = rocket_msg()
                        rocketmsg.timesFired = self.timesFired
                        
                        if self.timesFired >= 4:
                            self.defenseState = 1
                            rocketmsg.state = 1
                        else:
                            self.defenseState = 0
                            rocketmsg.state = 0
                        self.rocketPub.publish(rocketmsg)

                else: #lost
                    self.rocket.DOWN(100.0)
                    self.lostCount = self.lostCount + 1
                    if self.lostCount >= 45:
                        self.spinDirection = -self.spinDirection
                        self.lostCount = 0

                    if self.spinDirection is 1:
                        self.rocket.RIGHT(100.0)
                    else:
                        self.rocket.LEFT(100.0)

            #else:
                #print 'defense'

            rate.sleep()


if __name__ == '__main__':
    try:
        print "main"
        rocket = rocket_node()
        #print "rocket node"
        rocket.main_loop()

    except rospy.ROSInterruptException:
        pass

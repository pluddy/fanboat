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
    yawState = None
    pitchState = None
    fire = None
    timer = 0
    lost = 1
   
    def __init__(self):
        rospy.init_node('rocket_node')
        

    def init_subcribers(self):
        print "init subs"
        rospy.Subscriber('/rocket_command', rocket_msg, self.rocket_callback)
        rospy.Subscriber('/ballLandInfo', ballLandInfo, self.camCallback)
    #def init_publishers(self):
        #self.publisher1 = rospy.Publisher('rocket_topic',)

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
        print 'msg\n'

    def camCallback(self, ballLandInfo):
        
        x = ballLandInfo.x
        y = ballLandInfo.y
        t = ballLandInfo.type
        d = ballLandInfo.distance
        
        self.calculateTurnage(x, y, d)


    def main_loop(self):
        #self.init_publishers
        #print "loop"
        self.init_subcribers()
        #self.init_params
        rate = rospy.Rate(10);
        rocket = armageddon.Armageddon()
        
        while not rospy.is_shutdown():
            if self.timer > 0:
                self.timer = self.timer - 1
            print self.timer
    
            if self.lost is 0:
                if self.yawState is 0 and self.pitchState is 0:
                    #rocket.STOP()
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
                    rocket.FIRE()
                    self.timer =100 
                    print "fire"
            else: #lost
                print "lost"
                rocket.STOP()
              
            rate.sleep()

if __name__ == '__main__':
    try:
        print "main"
        rocket = rocket_node()
        print "rocket node"
        rocket.main_loop()



    except rospy.ROSInterruptException:
        pass

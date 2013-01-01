#!/usr/bin/env python

import rospy
import armageddon
from project.msg import rocket_msg

class rocket_node(object):
    #publisher1 = None
    #publisher2 = None
    subscriber1 = None
    
    def __init__(self):
        rospy.init_node('rocket_node')

    def init_subcribers(self):
        print "init subs"
        rospy.Subscriber('/rocket_command', rocket_msg, self.rocket_callback)
    #def init_publishers(self):
        #self.publisher1 = rospy.Publisher('rocket_topic',)
    def rocket_callback(self, rocket_msg):
        launcher = armageddon.Armageddon()
        if rocket_msg.stop == 1:
            launcher.STOP()
        elif rocket_msg.fire == 1:
            launcher.FIRE()
        elif rocket_msg.angle != 0.0:
            print("turn plz")
            launcher.LEFT(1000.0)
            launcher.RIGHT(2500.0)

    def main_loop(self):
        #self.init_publishers
        #print "loop"
        self.init_subcribers()
        #self.init_params
        rate = rospy.Rate(15);
        
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

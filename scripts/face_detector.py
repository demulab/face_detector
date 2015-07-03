#!/usr/bin/env python
import roslib
import sys
import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

class image_converter:
    def __init__(self):
        self.image_pub = rospy.Publisher("image_topic",Image)
        
        cv2.namedWindow("Image window",1)
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("/image_raw",Image,self.callback)
    def callback(self,data):
        try:
            cv2.image = self.bridge.imgmsg_to_cv2(data,"bgr8")
        except CvBridgeError,e:
            print e
        
        (rows,cols,channels) = cv2.image.shape
        if cols > 60 and rows > 60:
            cv2.circle(cv2.image,(50,50),10,255)

        cv2.imshow("Image window",cv2.image)
        cv2.waitKey(3)

        try:
            self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv2.image,"bgr8"))
        except CvBridgeError, e:
            print e

def main(args):
    ic = image_converter()
    rospy.init_node("image_converter",anonymous=True)
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print "Shutting down"
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main(sys.argv)

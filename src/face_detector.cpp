#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ros/ros.h>
#include <string>
#include <image_transport/image_transport.h>
#include <image_transport/simple_publisher_plugin.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/Int32.h>

void face_detector(const sensor_msgs::ImageConstPtr &msg){
  cv::CascadeClassifier fc("../config/haarcascade_frontalface_alt.xml");
  cv::Mat image;
  try{
    image = cv_bridge::toCvShare(msg,"bgr8")->image;
  }
  catch(cv_bridge::Exception& e){
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
  cv::cvtColor(image,image,cv::COLOR_BGR2GRAY);
  std::vector<cv::Rect> faces;
  fc.detectMultiScale(image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));

  /*for(int i = 0; i < faces.size(); i++){
    for(int j = 0; j < faces[i].size(); j++){
      cv::Point center(faces[i][j].x + faces[i][j].width*0.5,faces[i][j].y + faces[i][j].height*0.5);
      cv::ellipse( image, center, cv::Size( faces[i][j].width*0.5, faces[i][j].height*0.5), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
    }
    }*/
  //cv::imshow("face_detector",image);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "face_detector");
  ros::NodeHandle nh;
  cv::namedWindow("face_detector");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("/image_raw",1,face_detector);
  ros::spin();
  cv::destroyWindow("face_detector");
}
    

#include "ros/ros.h"
#include "ros_tutorials_topic/MsgTutorial.h"

//메세지를 수신했을때 동작하는 함수
void msgCallback(const ros_tutorials_topic::MsgTutorial::ConstPtr& msg)
{
    ROS_INFO("recieve msg = %d", msg->stamp.sec);
    ROS_INFO("recieve msg = %d", msg->stamp.nsec);
    ROS_INFO("recieve msg = %d", msg->data);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "topic_subscriber");

    ros::NodeHandle nh;

    //서브스크라이버 선언, ros_tutorial_msg라는 토픽을 작성 , 큐사이즈는 100개, 콜백함수 선언
    ros::Subscriber ros_tutorial_sub = nh.subscribe("ros_tutorial_msg", 100, msgCallback);

    ros::spin(); //콜백함수 호출 -> 수신되었을 경우 실행

    return 0;
}
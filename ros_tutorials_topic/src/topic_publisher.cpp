#include "ros/ros.h"
#include "ros_tutorials_topic/MsgTutorial.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "topic_publisher"); //노드명 초기화
    ros::NodeHandle nh;

    
    // 퍼블리셔 선언, ros_tutorial_msg라는 이름의 토픽을 생성, 큐사이즈 100
    ros::Publisher ros_tutorial_pub = nh.advertise<ros_tutorials_topic::MsgTutorial>("ros_tutorial_msg",100); 
    

    ros::Rate loop_rate(10); //루프 주기 설정 10Hz

    ros_tutorials_topic::MsgTutorial msg;
    int cnt = 0;

    while(ros::ok()){
        msg.stamp = ros::Time::now();
        msg.data = cnt;

        ROS_INFO("send msg = %d", msg.stamp.sec);
        ROS_INFO("send msg = %d", msg.stamp.nsec);
        ROS_INFO("send msg = %d", msg.data);

        ros_tutorial_pub.publish(msg); //메세지 발행

        loop_rate.sleep();

        ++cnt;
    }

    return 0;
}
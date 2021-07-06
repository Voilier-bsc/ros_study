#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <ros_tutorials_action/FibonacciAction.h>

int main(int argc, char** argv){
    ros::init(argc,argv,"action_client");

    //action client 선언
    actionlib::SimpleActionClient<ros_tutorials_action::FibonacciAction> ac("ros_tutorial_action",true);

    ROS_INFO("waiting for action server to start.");
    ac.waitForServer();

    ROS_INFO("Action server started, spending goal.");
    ros_tutorials_action::FibonacciGoal goal;   //action 목표 선언
    goal.order = 20;                            //action 목표 지정
    ac.sendGoal(goal);                          //action 목표 전송

    // 액션 목표 달성 제한 시간 설정
    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

    // 액션 목표 달정 제한 시간내에 액션 결과가 수신 된 경우
    if (finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s",state.toString().c_str());
    }
    else
        ROS_INFO("Action did not finish before the time out."); //제한시간 넘긴 경우

    return 0;
}
#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <ros_tutorials_action/FibonacciAction.h>

class FibonacciAction{
protected:
    ros::NodeHandle nh_;

    //action server definition
    actionlib::SimpleActionServer<ros_tutorials_action::FibonacciAction> as_;

    //action name
    std::string action_name_;

    ros_tutorials_action::FibonacciFeedback feedback_;
    ros_tutorials_action::FibonacciResult result_;

public:

    //initialize action server
    FibonacciAction(std::string name) :
        as_(nh_,name,boost::bind(&FibonacciAction::executeCB, this, _1), false),
        action_name_(name){
            as_.start();
        }

    ~FibonacciAction(void){

    }

    // action goal message를 받아 지정된 action을 수행하는 함수
    void executeCB(const ros_tutorials_action::FibonacciGoalConstPtr &goal){
        ros::Rate r(1);         //1Hz
        bool success = true;    //action의 성공 실패 저장하는 변수로 사용

        feedback_.sequence.clear();
        feedback_.sequence.push_back(0);
        feedback_.sequence.push_back(1);

        //action의 이름, 목표, 피보나치 수열의 초기 두개의 값을 info
        ROS_INFO("%s: Executing, creating fibonacci sequence of order %i with seeds %i, %i", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);

        for(int i = 1; i <= goal->order; i++){
            if(as_.isPreemptRequested() || !ros::ok())
            {
                ROS_INFO("%s: Preempted", action_name_.c_str());
                as_.setPreempted();
                success = false;
                break;
            }
            feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i-1]);
            as_.publishFeedback(feedback_); //feedback을 퍼블리시
            r.sleep();

        }
        if(success){
            result_.sequence = feedback_.sequence;
            ROS_INFO("%s: Succeeded", action_name_.c_str());
            as_.setSucceeded(result_);
        }
    }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "action_server");             //노드명 초기화
    FibonacciAction fibonacci("ros_tutorial_action");   //fibonacci 선언
    ros::spin();                                        //action 목표의 수신까지 대기
    return 0;
}
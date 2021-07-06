# ros_study
## file list
ros_tutorials_topic   -> 간단한 토픽사용 예제 (subscriber, publisher)

ros_tutorials_service -> 간단한 서비스 사용 예제 (server, client)

1. service의 경우 request와 response 로 나누지며 이때 ---를 이용해서 구분한다.
2. param을 설정한 후 설정한 parameter에 따라 다른 response를 얻을 수 있다.
   1. 파라미터 설정
      1. rosparam set <parameter 이름> <변경사항>
   2. 서비스 요청
      1. rosservice call <service 이름> <request>
    

ros_tutorials_action  -> 액션 사용 예제 (server, client)
        
1. action의 경우 goal, result, feedback 형태로 나누어진다.
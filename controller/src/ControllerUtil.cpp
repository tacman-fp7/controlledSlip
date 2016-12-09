#include "controlledSlip/ControllerUtil.h"

#include "sensor_msgs/JointState.h"


using controlledSlip::ControllerUtil;


ControllerUtil::ControllerUtil(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}

bool ControllerUtil::init(ros::NodeHandle &nodeHandle){

    jointCmdPub = nodeHandle.advertise<sensor_msgs::JointState>("/allegroHand/joint_cmd",1);

    // for loop to be removed!!!
    for(int i = 0; i < 16; i++){
        initialJointState.position[i] = 0.0;
    }
    //initialJointState = incomingData->actualJointState;

    incomingData->targetJointState = initialJointState;

    return true;
}

bool ControllerUtil::openHand(){

    std::vector<int> joints(16,0.0);
    std::vector<double> angles(16,0.0);

    joints[0] = 0; angles[0] = 0.0;
    joints[1] = 0; angles[1] = 0.0;
    joints[2] = 0; angles[2] = 0.0;
    joints[3] = 0; angles[3] = 0.0;
    joints[4] = 0; angles[4] = 0.0;
    joints[5] = 0; angles[5] = 0.0;
    joints[6] = 0; angles[6] = 0.0;
    joints[7] = 0; angles[7] = 0.0;
    joints[8] = 0; angles[8] = 0.0;
    joints[9] = 0; angles[9] = 0.0;
    joints[10] = 0; angles[10] = 0.0;
    joints[11] = 0; angles[11] = 0.0;
    joints[12] = 0; angles[12] = 1.39;
    joints[13] = 0; angles[13] = 0.0;
    joints[14] = 0; angles[14] = 0.0;
    joints[15] = 0; angles[15] = 0.0;

    moveJoints(joints,angles,2.0,0.05);

	return true;
}

bool ControllerUtil::graspApproach(){

    return true;
}

bool ControllerUtil::moveJoint(int joint,double angle){

    setJoint(joint,angle);
    sendJoints();

    return true;
}

bool ControllerUtil::moveJoints(const std::vector<int> &joints,std::vector<double> angles,double time = 2.0,double stepSize = 0.05){

    sensor_msgs::JointState startingJointState = incomingData->targetJointState;

    std::cout << "joints: ";
    for(int j = 0; j < 16; j++) std::cout << incomingData->targetJointState.position[j] << " ";
    std::cout << "\n";

    for(int currTime = 0; currTime < time + stepSize; currTime += stepSize){
    
        double ratio = currTime/time;
        if (ratio > 1.0){
            ratio = 1.0;
        }

        for(int i = 0; i < joints.size(); i++){

            incomingData->targetJointState.position[joints[i]] = startingJointState.position[joints[i]] + ratio*(angles[i]-startingJointState.position[joints[i]]);
        }

        sendJoints();

        ros::Duration(stepSize).sleep();

    std::cout << "joints: ";
    for(int j = 0; j < 16; j++) std::cout << incomingData->targetJointState.position[j] << " ";
    std::cout << "\n";

    }


    return true;
}


bool ControllerUtil::setJoint(int joint,double angle){

    incomingData->targetJointState.position[joint] = angle;

    return true;
}

void ControllerUtil::sendJoints(){

    jointCmdPub.publish(incomingData->targetJointState);
}


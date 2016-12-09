#include "controlledSlip/ControllerUtil.h"

#include "sensor_msgs/JointState.h"

using controlledSlip::ControllerUtil;


ControllerUtil::ControllerUtil(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}

bool ControllerUtil::init(ros::NodeHandle &nodeHandle){

    jointCmdPub = nodeHandle.advertise<sensor_msgs::JointState>("/allegroHand/joint_cmd",1);

    return true;
}

bool ControllerUtil::openHand(){

	return true;
}

bool ControllerUtil::graspApproach(){

    return true;
}

bool ControllerUtil::moveJoint(int jointNumber,double angle){

    return true;
}

void ControllerUtil::updateJoints(){

    jointCmdPub.publish(incomingData->targetJointState);
}



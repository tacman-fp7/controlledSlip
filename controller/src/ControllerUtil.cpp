#include "controlledSlip/ControllerUtil.h"

#include "std_msgs/String.h"

using controlledSlip::ControllerUtil;


ControllerUtil::ControllerUtil(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}

bool ControllerUtil::init(ros::NodeHandle &nodeHandle){

    encodersPub = nodeHandle.advertise<std_msgs::String>("encoders",1);

    return true;
}

bool ControllerUtil::openHand(){

	return true;
}

bool ControllerUtil::graspApproach(){

    return true;
}

bool moveJoint(int jointNumber,double angle){

    return true;
}



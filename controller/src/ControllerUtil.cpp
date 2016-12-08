#include "controlledSlip/ControllerUtil.h"

using controlledSlip::ControllerUtil;


ControllerUtil::ControllerUtil(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}

bool ControllerUtil::init(ros::NodeHandle &nodeHandle){

    encodersPub = nodeHandle.advertise<std_msgs::String>("encoders",1);
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



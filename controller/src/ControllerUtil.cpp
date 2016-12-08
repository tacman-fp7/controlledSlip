#include "controlledSlip/ControllersUtil.h"

using controlledSlip::ControllerUtil;


ControllerUtil::ControllerUtil(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}

bool ControllerUtil::init(){

    // initialize publisher
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



#include "controlledSlip/ControllerUtil.h"

#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

#define NO_CONTACT 0
#define STABLE_CONTACT 1
#define SLIP_DETECTED 2

using controlledSlip::ControllerUtil;


ControllerUtil::ControllerUtil(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}

bool ControllerUtil::init(ros::NodeHandle &nodeHandle){

    jointCmdPub = nodeHandle.advertise<sensor_msgs::JointState>("/allegroHand_0/joint_cmd",1);

    //pacVariancePub = nodeHandle.advertise<std_msgs::Float64>("/pacVariance",1);

    initialJointState = incomingData->actualJointState;

    incomingData->targetJointState = initialJointState;

    return true;
}

bool ControllerUtil::openHand(){

    std::vector<int> joints(16);
    std::vector<double> angles(16);

// 3 fingers
//    joints[0] = 0; angles[0] = 0.13;
//    joints[1] = 1; angles[1] = 0.8; // variable
//    joints[2] = 2; angles[2] = -0.17;
//    joints[3] = 3; angles[3] = -0.23;
//    joints[4] = 4; angles[4] = 0.13;
//    joints[5] = 5; angles[5] = 0.8; // variable
//    joints[6] = 6; angles[6] = -0.17;
//    joints[7] = 7; angles[7] = -0.23;
//    joints[8] = 8; angles[8] = 0.0;
//    joints[9] = 9; angles[9] = 0.0;
//    joints[10] = 10; angles[10] = 0.0;
//    joints[11] = 11; angles[11] = 0.0;
//    joints[12] = 12; angles[12] = 1.40;
//    joints[13] = 13; angles[13] = 0.0;
//    joints[14] = 14; angles[14] = 0.42; // variable
//    joints[15] = 15; angles[15] = -0.17;



// 2 fingers for quite large objects
//    joints[0] = 0; angles[0] = 0.139;
//    joints[1] = 1; angles[1] = 0.8; // variable
//    joints[2] = 2; angles[2] = 0.2; //0.492;
//    joints[3] = 3; angles[3] = -0.238;
//    joints[4] = 4; angles[4] = 0.0;
//    joints[5] = 5; angles[5] = 0.0; // variable
//    joints[6] = 6; angles[6] = 0.0;
//    joints[7] = 7; angles[7] = 0.0;
//    joints[8] = 8; angles[8] = 0.0;
//    joints[9] = 9; angles[9] = 0.0;
//    joints[10] = 10; angles[10] = 0.0;
//    joints[11] = 11; angles[11] = 0.0;
//    joints[12] = 12; angles[12] = 1.226;
//    joints[13] = 13; angles[13] = 0.051;
//    joints[14] = 14; angles[14] = 0.260; // variable
//    joints[15] = 15; angles[15] = -0.066;

// 2 fingers for the wooden object
    joints[0] = 0; angles[0] = 0.212;
    joints[1] = 1; angles[1] = 1.2; // variable
    joints[2] = 2; angles[2] = 0.295; //0.492;
    joints[3] = 3; angles[3] = -0.284;
    joints[4] = 4; angles[4] = 0.0;
    joints[5] = 5; angles[5] = 0.0; // variable
    joints[6] = 6; angles[6] = 0.0;
    joints[7] = 7; angles[7] = 0.0;
    joints[8] = 8; angles[8] = 0.0;
    joints[9] = 9; angles[9] = 0.0;
    joints[10] = 10; angles[10] = 0.0;
    joints[11] = 11; angles[11] = 0.0;
    joints[12] = 12; angles[12] = 1.151;//1.191
    joints[13] = 13; angles[13] = -0.043;
    joints[14] = 14; angles[14] = 0.414; // variable
    joints[15] = 15; angles[15] = -0.279;

    moveJoints(joints,angles,2.0,0.01);

	return true;
}

bool ControllerUtil::graspApproach(double angleStep,double timeStep){

    int nJoints = 3;

    std::vector<int> joints(nJoints);
    std::vector<int> fingers(nJoints);
    std::vector<int> thresholds(nJoints);
    std::vector<double> maxAngles(nJoints);
    std::vector<bool> contact(nJoints,false);
    std::vector<bool> disabled(nJoints);
    bool allInContact = false;

    int ind;
    ind = 0;
    joints[ind] = 1;  fingers[ind] = 0; thresholds[ind] = 100; maxAngles[ind] = 2.0; disabled[ind] = false;
    ind++;
    //joints[ind] = 5;  fingers[ind] = 1; thresholds[ind] = 300; maxAngles[ind] = 1.6; disabled[ind] = false;
    //ind++;
    joints[ind] = 14; fingers[ind] = 3; thresholds[ind] = 100; maxAngles[ind] = 0.6; disabled[ind] = true;

//    while(!allInContact){

    while(ros::ok() && !keyPressed()){
        for(int i = 0; i < joints.size(); i++){
            if (!contact[i] && !disabled[i]){
                double newAngle = incomingData->targetJointState.position[joints[i]] + angleStep;
                if (newAngle < maxAngles[i]){
                    incomingData->targetJointState.position[joints[i]] = newAngle;
                }
            }
        }

        for(int i = 0; i < joints.size(); i++){
            std::cout << fingers[i] << ": " << contact[i] << " " << incomingData->targetJointState.position[joints[i]] << "   ";
        }
        std::cout << "\n";

        sendJoints();

        ros::Duration(timeStep).sleep();

        for(int i = 0; i < joints.size(); i++){
            contact[i] = incomingData->bioTacData.BTTared[fingers[i]].Pdc > thresholds[i];
        }

        allInContact = true;
        for(int i = 0; i < joints.size() && allInContact; i++){
            allInContact = allInContact && contact[i];
        }

    }


    return true;
}

bool ControllerUtil::releaseForce(double angleStep,double timeStep){

    int jointToMove = 1;

    while (ros::ok() && !keyPressed()){
        
        incomingData->targetJointState.position[jointToMove] -= angleStep;
        sendJoints();

        ros::Duration(timeStep).sleep();

        //std::cout << "PAC Variance: " << incomingData->getBioTacPACVariance() << "\n";

        //incomingData->debugData.data = incomingData->getBioTacPACVariance();
        //pacVariancePub.publish(incomingData->debugData);
    }

    return true;
}

bool ControllerUtil::increaseForceMultipleTimes(double angleStep,double timeStep){

    int jointToMove = 1;

    double threshold = 140,thresholdStepSize = 40;

    angleStep = 0.0012;

    while (ros::ok() && !keyPressed()){
        
        
        if (incomingData->bioTacData.BTTared[0].Pdc < threshold){
            incomingData->targetJointState.position[jointToMove] += angleStep;
        } else {
            ros::Duration(2.0).sleep();
            threshold += thresholdStepSize;
        }

        sendJoints();

        ros::Duration(timeStep).sleep();


    }

    return true;
}

bool ControllerUtil::releaseAndIncreaseForce(double angleStep,double timeStep){

    int jointToMove = 1;

    

    double minLimit = 105,maxLimit = 140;
    bool slipping = false;

    while (ros::ok() && !keyPressed()){

        if (incomingData->bioTacData.BTTared[0].Pdc > minLimit && !slipping){
        
            incomingData->targetJointState.position[jointToMove] -= angleStep;

        } else {

            slipping = true;
            if (incomingData->bioTacData.BTTared[0].Pdc < maxLimit){
                incomingData->targetJointState.position[jointToMove] += angleStep*5;
            } else {
                slipping = false;
            }

        }
        sendJoints();

        ros::Duration(timeStep).sleep();

        //std::cout << "PAC Variance: " << incomingData->getBioTacPACVariance() << "\n";

        //incomingData->debugData.data = incomingData->getBioTacPACVariance();
        //pacVariancePub.publish(incomingData->debugData);
    }

    return true;
}

bool ControllerUtil::controlGrasp(double angleStepFW,double angleStepBW,double timeStep){

    int jointToMove = 1;
    int fingerNum = 0;
    int slipLabel;

    while (ros::ok() && !keyPressed()){
        
        slipLabel = incomingData->slipLabels.data[fingerNum];

        if (slipLabel == NO_CONTACT || slipLabel == SLIP_DETECTED){
            incomingData->targetJointState.position[jointToMove] += angleStepFW;
        } else {
            incomingData->targetJointState.position[jointToMove] -= angleStepBW;
        }
        
        sendJoints();

        ros::Duration(timeStep).sleep();
    }

    return true;
}


bool ControllerUtil::moveJoint(int joint,double angle){

    setJoint(joint,angle);
    sendJoints();

    return true;
}

bool ControllerUtil::moveJoints(const std::vector<int> &joints,std::vector<double> angles,double time = 2.0,double timeStep = 0.05){

    sensor_msgs::JointState startingJointState = incomingData->targetJointState;


    for(double currTime = 0.0; currTime < time + timeStep; currTime += timeStep){
        
        double ratio = currTime/time;
        if (ratio > 1.0){
            ratio = 1.0;
        }

        for(int i = 0; i < joints.size(); i++){

            incomingData->targetJointState.position[joints[i]] = startingJointState.position[joints[i]] + ratio*(angles[i]-startingJointState.position[joints[i]]);
        }

        sendJoints();

        ros::Duration(timeStep).sleep();

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

void ControllerUtil::waitForNextPhase(){

    while (ros::ok() && !keyPressed()){
        ros::Duration(0.05).sleep();
    }


}

bool ControllerUtil::keyPressed(){

    if (incomingData->keyPressed == true){
        incomingData->keyPressed = false;
        return true;
    }
    return false;
}




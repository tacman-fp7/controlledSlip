#include "controlledSlip/ControllerUtil.h"

#include "sensor_msgs/JointState.h"


using controlledSlip::ControllerUtil;


ControllerUtil::ControllerUtil(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}

bool ControllerUtil::init(ros::NodeHandle &nodeHandle){

    jointCmdPub = nodeHandle.advertise<sensor_msgs::JointState>("/allegroHand_0/joint_cmd",1);

    // for loop to be removed!!!
    //for(int i = 0; i < 16; i++){
    //    std::cout << "ciao" << i << "\n" << std::flush;
    //    initialJointState.position[i] = 0.0;
    //}
    initialJointState = incomingData->actualJointState;

    incomingData->targetJointState = initialJointState;

    return true;
}

bool ControllerUtil::openHand(){

    std::vector<int> joints(16);
    std::vector<double> angles(16);

    joints[0] = 0; angles[0] = 0.0;
    joints[1] = 1; angles[1] = 0.0;
    joints[2] = 2; angles[2] = 0.5;
    joints[3] = 3; angles[3] = 0.0;
    joints[4] = 4; angles[4] = 0.0;
    joints[5] = 5; angles[5] = 0.0;
    joints[6] = 6; angles[6] = 0.5;
    joints[7] = 7; angles[7] = 0.0;
    joints[8] = 8; angles[8] = 0.0;
    joints[9] = 9; angles[9] = 0.0;
    joints[10] = 10; angles[10] = 0.0;
    joints[11] = 11; angles[11] = 0.0;
    joints[12] = 12; angles[12] = 1.39;
    joints[13] = 13; angles[13] = 0.0;
    joints[14] = 14; angles[14] = 0.0;
    joints[15] = 15; angles[15] = 0.5;

    moveJoints(joints,angles,2.0,0.05);

	return true;
}

bool ControllerUtil::graspApproach(double angleStep,double timeStep){

    std::vector<int> joints(3);
    std::vector<int> fingers(3);
    std::vector<int> thresholds(3);
    std::vector<double> maxAngles(3);
    std::vector<bool> contact(3,false);
    bool allInContact = false;

    joints[0] = 1; fingers[0] = 0; thresholds[0] = 50; maxAngles[0] = 1.5;
    joints[1] = 5; fingers[1] = 1; thresholds[1] = 50; maxAngles[1] = 1.5;
    joints[2] = 14; fingers[2] = 3; thresholds[2] = 50; maxAngles[2] = 1.5;

    while(!allInContact){

        for(int i = 0; i < joints.size(); i++){
            if (!contact[i]){
                double newAngle = incomingData->targetJointState.position[joints[i]] + angleStep;
                if (newAngle < maxAngles[i]){
                    incomingData->targetJointState.position[joints[i]] = newAngle;
                }
            }
        }

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

bool ControllerUtil::moveJoint(int joint,double angle){

    setJoint(joint,angle);
    sendJoints();

    return true;
}

bool ControllerUtil::moveJoints(const std::vector<int> &joints,std::vector<double> angles,double time = 2.0,double timeStep = 0.05){

    sensor_msgs::JointState startingJointState = incomingData->targetJointState;

    //std::cout << "joints: ";
    //for(int j = 0; j < 16; j++) std::cout << incomingData->targetJointState.position[j] << " ";
    //std::cout << "\n";

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

        //std::cout << "joints: ";
        //for(int j = 0; j < 16; j++) std::cout << incomingData->targetJointState.position[j] << " ";
        //std::cout << "\n";

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


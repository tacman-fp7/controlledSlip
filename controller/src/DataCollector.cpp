#include "controlledSlip/DataCollector.h"

using controlledSlip::DataCollector;


DataCollector::DataCollector(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}


bool DataCollector::subscribeAll(ros::NodeHandle &nodeHandle){

    // subscribe to the biotacs topic
    slipLabelsSub = nodeHandle.subscribe("slip_labels",1,&DataCollector::updateSlipLabelsCallback,this);
    // subscribe to the encoders topic
    actualJointStateSub = nodeHandle.subscribe("/allegroHand_0/joint_states",1,&DataCollector::updateJointStateCallback,this);
    // subscribe to the biotacs topic
    encodersSub = nodeHandle.subscribe("/biotacs",1,&DataCollector::updateBioTacDataCallback,this);

}


void DataCollector::updateSlipLabelsCallback(const std_msgs::Float64MultiArray& slipLabels){

    incomingData->slipLabels = slipLabels;
    if (!incomingData->slipLabelsReady){
        incomingData->slipLabelsReady = true;
    }
}


void DataCollector::updateJointStateCallback(const sensor_msgs::JointState& actualJointState){

    incomingData->actualJointState = actualJointState;
    if (!incomingData->actualJointStateReady){
        incomingData->actualJointStateReady = true;
    }
}


void DataCollector::updateBioTacDataCallback(const biotacs::BT& bioTacData){

    incomingData->bioTacData = bioTacData;
    if (!incomingData->bioTacDataReady){
        incomingData->bioTacDataReady = true;
    }
}


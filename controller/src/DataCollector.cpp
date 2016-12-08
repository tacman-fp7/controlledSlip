#include "controlledSlip/DataCollector.h"

using controlledSlip::DataCollector;


DataCollector::DataCollector(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}


bool DataCollector::subscribeAll(ros::NodeHandle &nodeHandle){

    // subscribe to the biotacs topic
    slipLabelsSub = nodeHandle.subscribe("slip_labels",1,updateSlipLabelsData);
    // subscribe to the encoders topic
    encodersSub = nodeHandle.subscribe("encoders",1,updateEncodersData);

}


void DataCollector::updateSlipLabelsData(){

    // TODO store slip labels data inside incomingData
}


void DataCollector::updateEncodersData(){

    // TODO store encoders data inside incomingData
}


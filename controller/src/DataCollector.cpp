#include "controlledSlip/DataCollector.h"

#include "std_msgs/String.h"

using controlledSlip::DataCollector;


DataCollector::DataCollector(controlledSlip::IncomingData *incomingData){

    this->incomingData = incomingData;
}


bool DataCollector::subscribeAll(ros::NodeHandle &nodeHandle){

    // subscribe to the biotacs topic
    slipLabelsSub = nodeHandle.subscribe("slip_labels",1,&DataCollector::updateSlipLabelsData,this);
    // subscribe to the encoders topic
    encodersSub = nodeHandle.subscribe("encoders",1,&DataCollector::updateEncodersData,this);

}


void DataCollector::updateSlipLabelsData(const std_msgs::String::ConstPtr& msg){

    // TODO store slip labels data inside incomingData
}


void DataCollector::updateEncodersData(const std_msgs::String::ConstPtr& msg){

    // TODO store encoders data inside incomingData
}


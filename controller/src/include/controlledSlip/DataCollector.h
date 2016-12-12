#ifndef __CONTROLLEDSLIP_DATACOLLECTOR_H__
#define __CONTROLLEDSLIP_DATACOLLECTOR_H__

#include "controlledSlip/IncomingData.h"

#include "ros/ros.h"
#include "biotacs/BT.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64MultiArray.h"
#include "keyboard/Key.h"

namespace controlledSlip {

    class DataCollector {

        private:

            controlledSlip::IncomingData *incomingData;
            ros::Subscriber slipLabelsSub;
            ros::Subscriber actualJointStateSub;
            ros::Subscriber encodersSub;
            ros::Subscriber keyPressedSub;

        public:

			DataCollector(controlledSlip::IncomingData *incomingData);

            bool subscribeAll(ros::NodeHandle &nodeHandle);

            void updateSlipLabelsCallback(const std_msgs::Float64MultiArray& slipLabels);

            void updateJointStateCallback(const sensor_msgs::JointState& jointState);

            void updateBioTacDataCallback(const biotacs::BT& bioTacData);

            void keyPressedCallBack(const keyboard::Key& keyPressed);

    };

} //namespace controlledSlip

#endif

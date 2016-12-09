#ifndef __CONTROLLEDSLIP_DATACOLLECTOR_H__
#define __CONTROLLEDSLIP_DATACOLLECTOR_H__

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "controlledSlip/IncomingData.h"

namespace controlledSlip {

    class DataCollector {

        private:

            controlledSlip::IncomingData *incomingData;
            ros::Subscriber slipLabelsSub;
            ros::Subscriber encodersSub;

        public:

			DataCollector(controlledSlip::IncomingData *incomingData);

            bool subscribeAll(ros::NodeHandle &nodeHandle);

            void updateSlipLabelsData(const std_msgs::String::ConstPtr& msg);

            void updateEncodersData(const std_msgs::String::ConstPtr& msg);

    };

} //namespace controlledSlip

#endif

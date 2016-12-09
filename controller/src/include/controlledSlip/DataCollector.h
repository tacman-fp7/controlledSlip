#ifndef __CONTROLLEDSLIP_DATACOLLECTOR_H__
#define __CONTROLLEDSLIP_DATACOLLECTOR_H__

#include "ros/ros.h"
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

        private:

            void updateSlipLabelsData();

            void updateEncodersData();

    };

} //namespace controlledSlip

#endif

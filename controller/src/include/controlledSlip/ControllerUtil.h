#ifndef __CONTROLLEDSLIP_CONTROLLERUTIL_H__
#define __CONTROLLEDSLIP_CONTROLLERUTIL_H__

#include "ros/ros.h"
#include "controlledSlip/IncomingData.h"

namespace controlledSlip {

    class ControllersUtil {

        private:

            controlledSlip::IncomingData *incomingData;
            ros::Publisher encodersPub;

        public:

			ControllerUtil(controlledSlip::IncomingData *incomingData);

            void init(ros::NodeHandle &nodeHandle);

            bool openHand();

            bool graspApproach();

            bool moveJoint(int jointNumber,double angle);


        private:


    };

} //namespace controlledSlip

#endif

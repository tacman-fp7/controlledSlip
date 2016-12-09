#ifndef __CONTROLLEDSLIP_CONTROLLERUTIL_H__
#define __CONTROLLEDSLIP_CONTROLLERUTIL_H__

#include "controlledSlip/IncomingData.h"

#include "ros/ros.h"

namespace controlledSlip {

    class ControllerUtil {

        private:

            controlledSlip::IncomingData *incomingData;
            ros::Publisher encodersPub;

        public:

			ControllerUtil(controlledSlip::IncomingData *incomingData);

            bool init(ros::NodeHandle &nodeHandle);

            bool openHand();

            bool graspApproach();

            bool moveJoint(int jointNumber,double angle);


        private:

            void updateJoints();

    };

} //namespace controlledSlip

#endif

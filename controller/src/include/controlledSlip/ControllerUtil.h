#ifndef __CONTROLLEDSLIP_CONTROLLERUTIL_H__
#define __CONTROLLEDSLIP_CONTROLLERUTIL_H__

#include "controlledSlip/IncomingData.h"

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"

#include <vector>

namespace controlledSlip {

    class ControllerUtil {

        private:

            controlledSlip::IncomingData *incomingData;
            ros::Publisher jointCmdPub;
            ros::Publisher pacVariancePub;
            sensor_msgs::JointState initialJointState;
            

        public:

			ControllerUtil(controlledSlip::IncomingData *incomingData);

            bool init(ros::NodeHandle &nodeHandle);

            bool openHand();

            bool graspApproach(double angleStep,double timeStep);

            bool increaseForceMultipleTimes(double angleStep,double timeStep);

            bool releaseForce(double angleStep,double timeStep);

            bool releaseAndIncreaseForce(double angleStep,double timeStep);

            bool controlGrasp(double angleStepFW,double angleStepBW,double timeStep);

            bool regrasp(double angleStep,double timeStep);

            bool moveJoint(int joint,double angle);

            bool moveJoints(const std::vector<int> &joints,std::vector<double> angles,double time,double stepSize);

            void waitForNextPhase();

            bool keyPressed();

        private:

            void sendJoints();

            bool setJoint(int joint,double angle);


    };

} //namespace controlledSlip

#endif

#ifndef __CONTROLLEDSLIP_INCOMINGDATA_H__
#define __CONTROLLEDSLIP_INCOMINGDATA_H__

#include "biotacs/BT.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"
#include "keyboard/Key.h"

namespace controlledSlip {

    class IncomingData {

        public:


            biotacs::BT bioTacData;
            bool bioTacDataReady;

            sensor_msgs::JointState actualJointState;
            bool actualJointStateReady;

            std_msgs::Float64MultiArray slipLabels;
            bool slipLabelsReady;

            keyboard::Key key;
            bool keyPressed;

            sensor_msgs::JointState targetJointState;

            std_msgs::Float64 debugData;



        public:

			IncomingData();

            double getBioTacPACVariance();

    };

} //namespace controlledSlip

#endif

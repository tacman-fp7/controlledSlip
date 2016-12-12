#ifndef __CONTROLLEDSLIP_INCOMINGDATA_H__
#define __CONTROLLEDSLIP_INCOMINGDATA_H__

#include "biotacs/BT.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"


namespace controlledSlip {

    class IncomingData {

        public:


            biotacs::BT bioTacData;
            sensor_msgs::JointState actualJointState;
            sensor_msgs::JointState targetJointState;
            std_msgs::Float64MultiArray slipLabels;

            std_msgs::Float64 debugData;


            bool bioTacDataReady;
            bool actualJointStateReady;
            bool slipLabelsReady;



        public:

			IncomingData();

            double getBioTacPACVariance();

    };

} //namespace controlledSlip

#endif

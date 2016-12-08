#ifndef __CONTROLLEDSLIP_CONTROLLERUTIL_H__
#define __CONTROLLEDSLIP_CONTROLLERUTIL_H__


namespace controlledSlip {

    class ControllersUtil {

        private:

            IncomingData *incomingData;

        public:

			ControllerUtil(controlledSlip::IncomingData *incomingData);

            void init();

            bool openHand();

            bool graspApproach();

            bool moveJoint(int jointNumber,double angle);


        private:


    };

} //namespace controlledSlip

#endif

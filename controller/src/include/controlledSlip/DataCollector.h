#ifndef __CONTROLLEDSLIP_DATACOLLECTOR_H__
#define __CONTROLLEDSLIP_DATACOLLECTOR_H__



namespace controlledSlip {

    class DataCollector {

        private:

            controlledSlip::IncomingData *incomingData;

        public:

			DataCollector(controlledSlip::IncomingData *incomingData);

            bool subscribeAll();

        private:

            void updateBioTacData();

            void updateEncodersData();

    };

} //namespace controlledSlip

#endif

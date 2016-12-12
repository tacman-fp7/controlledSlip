#include "controlledSlip/IncomingData.h"
#include "controlledSlip/DataCollector.h"
#include "controlledSlip/ControllerUtil.h"

#include "ros/ros.h"

#include <time.h>

using controlledSlip::IncomingData;
using controlledSlip::DataCollector;
using controlledSlip::ControllerUtil;


int main(int argc, char * argv[])
{

    // SETTINGS
    int numberOfThreads = 3; // it should match the number of subscribers
    double waitTimeDataReady = 0.5;
    double waitTimeBeforeGrasp = 2.0;
    int loopRateDebugging = 10;
    bool debuggingEnabled = false;
    double approachAngleStep = 0.002, approachTimeStep = 0.01;
    double slipAngleStepFW = 0.0001,slipAngleStepBW = 0.0002,slipTimeStep = 0.01;
    double forceReleaseAngleStep = 0.0001, forceReleaseTimeStep = 0.01;

    // initialize ROS
    ros::init(argc, argv, "controller");
    ros::NodeHandle nodeHandle;

    // incomingData contains all the data read from the topics (related to tactile sensors and encoders)
    IncomingData incomingData;

    // dataCollector takes care of keeping incomingData updated
    DataCollector dataCollector(&incomingData);
    dataCollector.subscribeAll(nodeHandle);

    // start the asyncronous spinner used to check if new data is available at the topics
    ros::AsyncSpinner spinner(numberOfThreads);
    spinner.start();

    // wait for all data to be ready
    ros::Duration(waitTimeDataReady).sleep();

    // controllerUtil is used to control the joints of the hand
    ControllerUtil controllerUtil(&incomingData);
    controllerUtil.init(nodeHandle);

    ros::Rate loopRate(loopRateDebugging);

    while (debuggingEnabled && ros::ok()){

        std::cout << "---------\n";

        std::cout << "Slip labels - ";
        if (incomingData.slipLabelsReady){
            for(int j = 0; j < 4; j++){
                std::cout <<  incomingData.slipLabels.data[j] << " - ";
            }
        } else {
            std::cout << "data not available";
        }
        std::cout << "\n";
        
        std::cout << "Biotac - ";
        if (incomingData.bioTacDataReady){
            for(int j = 0; j < 4; j++){
                std::cout <<  incomingData.bioTacData.BTTared[j].Pdc << " - ";
            }
        } else {
            std::cout << "data not available";
        }
        std::cout << "\n";
        
        std::cout << "Joints - ";
        if (incomingData.actualJointStateReady){
            for(int j = 0; j < 16; j++){
                std::cout << j << ": " << incomingData.actualJointState.position[j] << " - ";
            }
        } else {
            std::cout << "data not available";
        }
        std::cout << "\n";

        loopRate.sleep();
    }



    // open the hand
    controllerUtil.openHand();
    std::cout << "Initial position reached.\n";
    
    controllerUtil.waitForNextPhase();

    // move the fingers towards the object and stop as soon as contact is detected
    std::cout << "Starting approach phase.\n";
    controllerUtil.graspApproach(approachAngleStep,approachTimeStep);

    //std::cout << "Starting controlled slip.\n";
    //controllerUtil.controlSlip(slipAngleStepFW,slipAngleStepBW,slipTimeStep);

    std::cout << "Starting releasing force.\n";    
    controllerUtil.releaseForce(forceReleaseAngleStep,forceReleaseTimeStep);

    spinner.stop();

    return 0;
}

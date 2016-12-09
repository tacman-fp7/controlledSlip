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
    std::cout << "daf;kjadslfkjf";
    // initialize ROS
    ros::init(argc, argv, "controller");
    ros::NodeHandle nodeHandle;

    // incomingData contains all the data read from the topics (related to tactile sensors and encoders)
    IncomingData incomingData;

    // dataCollector takes care of keeping incomingData updated
    DataCollector dataCollector(&incomingData);
    dataCollector.subscribeAll(nodeHandle);

    // start the asyncronous spinner used to check if new data is available at the topics
    ros::AsyncSpinner spinner(3); // use 3 threads
    spinner.start();

    ros::Duration(0.5).sleep();

    // controllerUtil is used to control the joints of the hand
    ControllerUtil controllerUtil(&incomingData);
    controllerUtil.init(nodeHandle);

    ros::Rate loopRate(10);

    while (!ros::ok()){

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

    // TODO wait until a key is pressed

    // move the fingers towards the object and stop as soon as contact is detected
    //controllerUtil.graspApproach();

    // TODO run the controller to stabilize the grip

    spinner.stop();

    return 0;
}

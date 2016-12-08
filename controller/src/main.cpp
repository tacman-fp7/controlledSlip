#include "ros/ros.h"



int main(int argc, char * argv[])
{

    // initialize ROS
    ros::init(argc, argv, "controller");
    ros::NodeHandle nodeHandle;

    // incomingData contains all the data read from the topics (related to tactile sensors and encoders)
    IncomingData incomingData = new IncomingData();

    // dataCollector takes care of keeping incomingData updated
    DataCollector dataCollector = new DataCollector(&incomingData);
    dataCollector.subscribeAll(nodeHandle);

    // start the asyncronous spinner used to check if new data is available at the topics
    ros::AsyncSpinner spinner(3); // use 3 threads
    spinner.start();

    // controllerUtil is used to control the joints of the hand
    ControllerUtil controllerUtil = new ControllerUtil(&incomingData);
    controllerUtil.init(nodeHandle);

    // open the hand
    controllerUtil.openHand();

    // TODO wait until a key is pressed

    // move the fingers towards the object and stop as soon as contact is detected
    controllerUtil.graspApproach();

    // TODO run the controller to stabilize the grip

    // TODO stop the asyncronous spin

    return 0;
}

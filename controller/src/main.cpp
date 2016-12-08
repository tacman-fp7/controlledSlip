int main(int argc, char * argv[])
{

    // setup ROS

    IncomingData incomingData = new IncomingData();

    DataCollector dataCollector = new DataCollector(&incomingData);

    dataCollector.subscribeAll();

    // start the asyncronous spin

    ControllerUtil controllerUtil = new ControllerUtil(&incomingData);

    controllerUtil.init();

    controllerUtil.openHand();

    // wait until a key is pressed

    controllerUtil.graspApproach();

    // run the controller to stabilize the grip

    // stop the asyncronous spin

    return 0;
}

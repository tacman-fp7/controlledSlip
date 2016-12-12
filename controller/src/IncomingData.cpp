#include "controlledSlip/IncomingData.h"

using controlledSlip::IncomingData;


IncomingData::IncomingData(){

    bioTacDataReady = false;
    actualJointStateReady = false;
    slipLabelsReady = false;

}

double IncomingData::getBioTacPACVariance(){

    int fingerToUse = 0;
    double pacMean = 0;

    for(int i = 0; i < 22; i++){
        pacMean += bioTacData.BT[fingerToUse].Pac[i];
    }
    pacMean = pacMean/22;

    double pacVariance = 0;
    double currPac;
    for(int i = 0; i < 22; i++){
        currPac = bioTacData.BT[fingerToUse].Pac[i];
        pacVariance += (currPac - pacMean)*(currPac - pacMean);
    }
    pacVariance = pacVariance/22;

    return pacVariance;
}

/*
  ==============================================================================

    AdsrData.cpp
    Created: 10 May 2022 12:58:39am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release){
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release; //sec
    
    setParameters(adsrParams);
}

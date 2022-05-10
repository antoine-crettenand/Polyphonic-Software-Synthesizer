/*
  ==============================================================================

    AdsrData.h
    Created: 10 May 2022 12:58:39am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
};

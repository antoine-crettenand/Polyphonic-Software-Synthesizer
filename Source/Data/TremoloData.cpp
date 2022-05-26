/*
  ==============================================================================

    TremoloData.cpp
    Created: 21 May 2022 6:23:29pm
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "TremoloData.h"


void TremoloData::processBlock(juce::AudioBuffer<float>& buffer) {
    if (!isActive){
        return;
    }
    auto* leftBuffer  = buffer.getWritePointer (0);
    auto* rightBuffer = buffer.getWritePointer (1);
   
    for (auto i = 0; i < buffer.getNumSamples(); ++i)
    {
        float levelLeft = (oscLeft.processSample(1.f)) / 2.f;
        auto nextSampleLeft = leftBuffer[i] * levelLeft;
        leftBuffer[i]  = nextSampleLeft;
        
        float levelRight = (oscRight.processSample(1.f)) / 2.f;
        auto nextSampleRight = rightBuffer[i] * levelRight;
        rightBuffer[i]  = nextSampleRight;
    }
}

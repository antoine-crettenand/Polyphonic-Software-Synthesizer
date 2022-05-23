/*
  ==============================================================================

    TremoloData.cpp
    Created: 21 May 2022 6:23:29pm
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "TremoloData.h"


void TremoloData::processBlock(juce::AudioBuffer<float>& buffer) {
//    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    //0 for left
    auto* leftBuffer  = buffer.getWritePointer (0);
    auto* rightBuffer = buffer.getWritePointer (1);
   
    for (auto i = 0; i < buffer.getNumSamples(); ++i)
    {
        float levelLeft = (oscLeft.processSample(0.f) + 1) / 2;
        auto nextSampleLeft = leftBuffer[i] * levelLeft;
        leftBuffer[i]  = nextSampleLeft;
        
        float levelRight = (oscRight.processSample(0.f) + 1) / 2;
        auto nextSampleRight = rightBuffer[i] * levelRight;
        rightBuffer[i]  = nextSampleRight;
    }
}

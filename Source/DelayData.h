/*
  ==============================================================================

    DelayData.h
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once
# include "TimeEffectData.h"

class DelayData : public TimeEffectData
{
public :
    DelayData(float maxTimeDelay): TimeEffectData("delay", maxTimeDelay)
    {
    }
    void processBlock(juce::AudioBuffer<float>& buffer) override;

private :

    float delayTime = 1.0f;
};

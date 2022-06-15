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
    void update(juce::AudioProcessorValueTreeState& apvts) override;
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout) override;

private :

    float timeDelay = 1.0f;
    float gainDelay = 0.7f;
};

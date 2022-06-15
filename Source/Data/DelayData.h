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
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) override;
    void processBlock(juce::AudioBuffer<float>& buffer) override;
    void update(juce::AudioProcessorValueTreeState& apvts) override;
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout) override;

private :
    void fillDelayBuffer(juce::AudioBuffer<float>& delayBuffer);
    juce::AudioBuffer<float> delayBuffer;
    float timeDelay = 1.0f;
    float gainDelay = 0.7f;
};

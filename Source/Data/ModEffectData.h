/*
  ==============================================================================

    ModEffectData.h
    Created: 21 May 2022 10:00:01am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OscData.h"

struct ModSettings
{
    float freq { 0 };
     int waveType { 0 };
};


class ModEffectData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void processBlock(juce::AudioBuffer<float>& buffer);
    
    void update(juce::AudioProcessorValueTreeState& apvts);
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);


private:
    ModSettings getModSettings(juce::AudioProcessorValueTreeState& apvts);

    //use lambda function, another : ;
    OscData osc;
    
    juce::dsp::Gain<float> gain;
    //to enforce to use prepareToPlay
    bool isPrepared { false };
    
    
};
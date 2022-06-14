/*
  ==============================================================================

    TimeEffectData.h
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Data/OscData.h"
#include "CircularBuffer.h"



class TimeEffectData
{
public:
    TimeEffectData(const std::string &nameID, float maxTimeDelay):nameID(nameID), circularBuffer(maxTimeDelay)
    {
    }
    virtual ~TimeEffectData(){}
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    virtual void processBlock(juce::AudioBuffer<float>& buffer) = 0;
    
    virtual void update(juce::AudioProcessorValueTreeState& apvts);
    virtual void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    



protected:
    std::string nameID;
    bool isActive = true;
    CircularBuffer circularBuffer;
    juce::dsp::ProcessSpec spec;
    
    
private:

    //to enforce to use prepareToPlay
    bool isPrepared { false };
    
    
};

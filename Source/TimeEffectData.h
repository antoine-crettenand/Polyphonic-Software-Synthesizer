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

struct TimeSettings
{
    float freq { 0.f };
     int waveType { 0 };
    float shift { 0.f };
    bool isActive {false};
};


class TimeEffectData
{
public:
    TimeEffectData(const std::string &nameID, float maxTimeDelay):nameID(nameID), circularBuffer(maxTimeDelay)
    {
    }
    virtual ~TimeEffectData(){}
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    // TODO : check validity
//        virtual ~ModEffectData();
    virtual void processBlock(juce::AudioBuffer<float>& buffer) = 0;
    
    void update(juce::AudioProcessorValueTreeState& apvts);
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    



protected:
    //osc left not shifted in contrary to oscRight
    OscData oscLeft;
    OscData oscRight;
    std::string nameID;
    bool isActive = true;
    CircularBuffer circularBuffer;
    juce::dsp::ProcessSpec spec;
    
    
private:
    TimeSettings getTimeSettings(juce::AudioProcessorValueTreeState& apvts);

    //use lambda function, another : ;
    
    
//    juce::dsp::Gain<float> gain;
    //to enforce to use prepareToPlay
    bool isPrepared { false };
    
    
};

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
    float freq { 0.f };
     int waveType { 0 };
    float shift { 0.f };
    bool isActive {false};
};


class ModEffectData
{
public:
    ModEffectData(const std::string &nameID):nameID(nameID)
    {
    }
    virtual ~ModEffectData(){}
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    // TODO : check validity
//        virtual ~ModEffectData();
//    virtual void processBlock(juce::AudioBuffer<float>& buffer) = 0;
    virtual void processBlock(juce::AudioBuffer<float>& buffer) = 0;
    
    void update(juce::AudioProcessorValueTreeState& apvts);
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    



protected:
    //osc left not shifted in contrary to oscRight
    OscData oscLeft;
    OscData oscRight;
    std::string nameID;
    bool isActive = false;
    
private:
    ModSettings getModSettings(juce::AudioProcessorValueTreeState& apvts);

    //use lambda function, another : ;
    
    
//    juce::dsp::Gain<float> gain;
    //to enforce to use prepareToPlay
    bool isPrepared { false };
    
    
};

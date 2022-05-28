/*
  ==============================================================================

    DistortionData.h
    Created: 23 May 2022 10:38:40pm
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
using Filter = juce::dsp::IIR::Filter<float>;
using FilterCoefs = juce::dsp::IIR::Coefficients<float>;
using DistortionChain = juce::dsp::ProcessorChain<juce::dsp::ProcessorDuplicator<Filter, FilterCoefs>, juce::dsp::Gain<float>, juce::dsp::WaveShaper<float>, juce::dsp::Gain<float>>;

class DistortionData : public DistortionChain {
public:
    DistortionData() noexcept {
        distortionChain.get<DistortionData::ChainPositions::Waveshaper>().functionToUse = [] (float x)
                                   {
                                       return std::tanh (x);
                                   };
        // Default values
        auto& preGain = distortionChain.get<DistortionData::ChainPositions::PreGain>();
        preGain.setGainDecibels (30.0f);

        auto& postGain = distortionChain.get<DistortionData::ChainPositions::PostGain>();
        postGain.setGainDecibels (-20.0f);
    }
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(juce::AudioBuffer<float>& buffer);
    void update(juce::AudioProcessorValueTreeState& apvts);
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    
private:
    
    void reset();
    void updateHighpassFilter(float highPassFreq);
    
    double sampleRate;
    bool isPrepared = false;
    
    enum ChainPositions {
        Filter,
        PreGain,
        Waveshaper,
        PostGain
    };
    
    DistortionChain distortionChain;
};

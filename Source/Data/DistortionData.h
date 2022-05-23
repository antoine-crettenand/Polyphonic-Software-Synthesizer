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

class DistortionData : public juce::dsp::ProcessorChain<juce::dsp::ProcessorDuplicator<Filter, FilterCoefs>, juce::dsp::Gain<float>, juce::dsp::WaveShaper<float>, juce::dsp::Gain<float>> {
    
public:
    DistortionData() noexcept {
        this->template get<waveshaperIndex>().functionToUse = [] (float x)
                                   {
                                       return std::tanh (x);
                                   };

        // Default values
        auto& preGain = this->template get<preGainIndex>();
        preGain.setGainDecibels (30.0f);

        auto& postGain = this->template get<postGainIndex>();
        postGain.setGainDecibels (-20.0f);
    }
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(juce::AudioBuffer<float>& buffer);
    void update(float preGain, float postGain, float highPassFreq);
    
    
private:
    void reset();
    void prepareToPlay(const juce::dsp::ProcessSpec& specs);
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);

    template <typename ProcessContext>
    void process(const ProcessContext& context);
    
    float preGain;
    float postGain;
    float highPassFreq;
    
    double sampleRate;
    bool isPrepared = false;
    
    enum {
        filterIndex,
        preGainIndex,
        waveshaperIndex,
        postGainIndex
    };
};

//
//  FilterData.h
//  COM418
//
//  Created by Jonathan Reymond on 11.05.22.
//

#pragma once
#include <JuceHeader.h>

//    Aliases
    using Filter = juce::dsp::IIR::Filter<float>;
//    Chain of 4 iir filters (one for each slope)=> lowcut and highcut
//    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
//    Path of a mono source
    using MonoChain = juce::dsp::ProcessorChain<Filter, Filter, Filter>;

struct ChainSettings
{
    float peakFreq { 0 }, peakGainInDecibels { 0 }, peakQuality {1.f};
    float lowCutFreq { 0 }, highCutFreq { 0 };
};


class FilterData : public MonoChain
{
public:
    FilterData()
    {
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void updateFilters(juce::AudioProcessorValueTreeState& apvts);
    void processBlock(juce::AudioBuffer<float>& buffer);
    void setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    
private:
    MonoChain chain;
    
    double sampleRate;
    bool isPrepared = false;

    enum ChainPositions
    {
        LowCut,
        Peak,
        HighCut
    };
    ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);
    
    void updatePeakFilter(const ChainSettings& chainSettings);
    
    using Coefficients = Filter::CoefficientsPtr;
    
    static void updateCoefficients(Coefficients& old, const Coefficients& replacement);

    
    void updateLowCutFilter(const ChainSettings& chainSettings);
    void updateHighCutFilter(const ChainSettings& chainSettings);
    
    
};


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
    FilterData(double sampleRate){
        
    }
private:
    MonoChain chain;
    
    double sampleRate;
    
    double lowCutSlope = 1;
    double lowCutOrder = (lowCutSlope + 1)*2;
    
    double highCutSlope = 1;
    double highCutOrder = (highCutSlope + 1)*2;
    enum ChainPositions
    {
        LowCut,
        Peak,
        HighCut
    };
    
    void updatePeakFilter(const ChainSettings& chainSettings);
    
    using Coefficients = Filter::CoefficientsPtr;
    
    static void updateCoefficients(Coefficients& old, const Coefficients& replacement);
    
    template<int Index, typename CoefficientType>
    void updateCutFilter(const CoefficientType& coefficients)
    {
        updateCoefficients(chain.template get<Index>().coefficients, coefficients);
    }
    
    void updateLowCutFilter(const ChainSettings& chainSettings);
    void updateHighCutFilter(const ChainSettings& chainSettings);
    void updateFilters(const ChainSettings& chainSettings);
    
};


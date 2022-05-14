//
//  FilterData.cpp
//  COM418
//
//  Created by Jonathan Reymond on 11.05.22.
//

#include "FilterData.h"


void FilterData::updatePeakFilter(const ChainSettings &chainSettings){
    auto peakCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate,
                                                                                chainSettings.peakFreq,
                                                                                chainSettings.peakQuality,
                                                                                juce::Decibels::decibelsToGain(chainSettings.peakGainInDecibels));
    
    updateCoefficients(chain.get<FilterData::ChainPositions::Peak>().coefficients, peakCoefficients);
}


void FilterData::updateCoefficients(Coefficients& old, const Coefficients& replacement){
    *old = *replacement;
}


void FilterData::updateLowCutFilter(const ChainSettings& chainSettings){
    auto lowCutCoefficients = juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(chainSettings.lowCutFreq,
                                                                                                       sampleRate,
                                                                                                       lowCutOrder);
    updateCutFilter<FilterData::ChainPositions::LowCut>(lowCutCoefficients);
    
}

void FilterData::updateHighCutFilter(const ChainSettings& chainSettings){
    auto highCutCoefficients = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(chainSettings.highCutFreq,
                                                                                                       sampleRate,
                                                                                                       highCutOrder);

    updateCutFilter<FilterData::ChainPositions::LowCut>(highCutCoefficients);
}

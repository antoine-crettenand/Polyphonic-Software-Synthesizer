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
    auto lowCutCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate,
                                                                                chainSettings.lowCutFreq);
    updateCoefficients(chain.get<FilterData::ChainPositions::LowCut>().coefficients, lowCutCoefficients);
    
}

void FilterData::updateHighCutFilter(const ChainSettings& chainSettings){
    auto highCutCoefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate,
                                                                                chainSettings.highCutFreq);
    updateCoefficients(chain.get<FilterData::ChainPositions::HighCut>().coefficients, highCutCoefficients);
}

//
//  FilterData.cpp
//  COM418
//
//  Created by Jonathan Reymond on 11.05.22.
//

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    //Can process only one channel of audio
    spec.numChannels = 1;
    spec.sampleRate = sampleRate;
    //a dsp processorChain takes to instantiate the spec
    leftChain.prepare(spec);
    rightChain.prepare(spec);
    
    this->isPrepared = true;
}


void FilterData::updateFilters(juce::AudioProcessorValueTreeState& apvts){
    auto chainSettings = getChainSettings(apvts);
    updatePeakFilter(chainSettings);
    updateLowCutFilter(chainSettings);
    updateHighCutFilter(chainSettings);
}

ChainSettings FilterData::getChainSettings(juce::AudioProcessorValueTreeState& apvts){
    ChainSettings settings;
//in real units
    settings.lowCutFreq = apvts.getRawParameterValue("LowCutFreq")->load();
    settings.highCutFreq = apvts.getRawParameterValue("HighCutFreq")->load();

    settings.peakFreq = apvts.getRawParameterValue("PeakFreq")->load();
    settings.peakGainInDecibels = apvts.getRawParameterValue("PeakGain")->load();
    settings.peakQuality = apvts.getRawParameterValue("PeakQuality")->load();
    return settings;
}

void FilterData::processBlock(juce::AudioBuffer<float>& buffer){
    juce::dsp::AudioBlock<float> block(buffer);

    auto monoBlock0 = block.getSingleChannelBlock(0);
    juce::dsp::ProcessContextReplacing<float> monoContext0(monoBlock0);
    leftChain.process(monoContext0);

    auto monoBlock1 = block.getSingleChannelBlock(1);
    juce::dsp::ProcessContextReplacing<float> monoContext1(monoBlock1);
    rightChain.process(monoContext1);
//    for(auto i = 0; i < block.getNumChannels(); ++i)
//    {
//        auto monoBlock = block.getSingleChannelBlock(i);
//        juce::dsp::ProcessContextReplacing<float> monoContext(monoBlock);
//        chain.process(monoContext);
//    }
    
}

void FilterData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    /*
     Filter settings :
     LowCutFreq => lowCut frequency (20 - 20000 [Hz])
     HighCutFreq => highCut frequency (20 - 20000 [Hz])
     PeakFreq => peak frequency (20 - 20000 [Hz])
     PeakGain => Peak gain (-24 to +10 dB)
     PeakQuality => peak quality (0.1 - 10)
     */
    layout.add(std::make_unique<juce::AudioParameterFloat>("LowCutFreq",
                                                           "LowCutFreq",
                                                           juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f),
                                                            20.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("HighCutFreq",
                                                           "HighCutFreq",
                                                           juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f),
                                                           20000.f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("PeakFreq",
                                                           "PeakFreq",
                                                           juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f),
                                                           750.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("PeakGain",
                                                           "PeakGain",
                                                           juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f),
                                                           0.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("PeakQuality",
                                                           "PeakQuality",
                                                           juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f),
                                                           1.f));
    
}


void FilterData::updatePeakFilter(const ChainSettings &chainSettings){
    auto peakCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate,
                                                                                chainSettings.peakFreq,
                                                                                chainSettings.peakQuality,
                                                                                juce::Decibels::decibelsToGain(chainSettings.peakGainInDecibels));
    
    updateCoefficients(leftChain.get<FilterData::ChainPositions::Peak>().coefficients, peakCoefficients);
    updateCoefficients(rightChain.get<FilterData::ChainPositions::Peak>().coefficients, peakCoefficients);
}


void FilterData::updateCoefficients(Coefficients& old, const Coefficients& replacement){
    *old = *replacement;
}


void FilterData::updateLowCutFilter(const ChainSettings& chainSettings){
    auto lowCutCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate,
                                                                                chainSettings.lowCutFreq,
                                                                                0.1f);
    updateCoefficients(leftChain.get<FilterData::ChainPositions::LowCut>().coefficients, lowCutCoefficients);
    updateCoefficients(rightChain.get<FilterData::ChainPositions::LowCut>().coefficients, lowCutCoefficients);
    
}

void FilterData::updateHighCutFilter(const ChainSettings& chainSettings){
    auto highCutCoefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate,
                                                                                chainSettings.highCutFreq,
                                                                                0.1f);
    updateCoefficients(leftChain.get<FilterData::ChainPositions::HighCut>().coefficients, highCutCoefficients);
    updateCoefficients(rightChain.get<FilterData::ChainPositions::HighCut>().coefficients, highCutCoefficients);
}

/*
  ==============================================================================

    DistortionData.cpp
    Created: 23 May 2022 10:38:40pm
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include "DistortionData.h"

void DistortionData::prepareToPlay(double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;
    spec.sampleRate = sampleRate;

    updateHighpassFilter(1000.0f); // default value
    
    //a dsp processorChain takes to instantiate the spec
    distortionChain.prepare(spec);
    this->isPrepared = true;
}

void DistortionData::updateHighpassFilter(float highPassFreq){
    auto lowCutCoefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highPassFreq);
    *distortionChain.get<DistortionData::ChainPositions::Filter>().coefficients = *lowCutCoefficients;
}

void DistortionData::update(juce::AudioProcessorValueTreeState& apvts){
    auto preGain = apvts.getRawParameterValue("DistPreGain")->load();
    auto postGain = apvts.getRawParameterValue("DistPostGain")->load();
    auto highPassFreq = apvts.getRawParameterValue("DistHighPassFreq")->load();
    
    distortionChain.get<DistortionData::ChainPositions::PreGain>().setGainDecibels (preGain);
    distortionChain.get<DistortionData::ChainPositions::PostGain>().setGainDecibels (postGain);
    
    updateHighpassFilter(highPassFreq);
};


void DistortionData::processBlock(juce::AudioBuffer<float> &buffer){
    juce::dsp::AudioBlock<float> block(buffer);
    
    for(auto i = 0; i < block.getNumChannels(); ++i)
    {
        auto monoBlock = block.getSingleChannelBlock(i);
        juce::dsp::ProcessContextReplacing<float> monoContext(monoBlock);
        distortionChain.process(monoContext);
    }
};

void DistortionData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    /*
     Distortion settings :
     DistPreGain => pregain  (-60 : +60 [dB])
     HighPassFreq => lowCut frequency (20 : 20000 [Hz])
     DistPostGain => pregain  (-60 : +60 [dB])
     */
    layout.add(std::make_unique<juce::AudioParameterFloat>("DistPreGain",
                                                           "DistPreGain",
                                                           juce::NormalisableRange<float>(-60.0f, 60.f, 1.f, 1.f),
                                                            30.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DistHighPassFreq",
                                                           "DistHighPassFreq",
                                                           juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f),
                                                           1000.f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("DistPostGain",
                                                           "DistPostGain",
                                                           juce::NormalisableRange<float>(-60.0f, 60.f, 1.f, 1.f),
                                                           -20.f));
};

/*
  ==============================================================================

    DistortionData.cpp
    Created: 23 May 2022 10:38:40pm
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include "DistortionData.h"

DistortionData::DistortionData() noexcept {
    auto& waveShaper = distortionChain.get<DistortionData::ChainPositions::Waveshaper>();
    waveShaper.functionToUse = [] (auto x)
    {
        return std::tanh(x);
    };
    
    // Default values
    auto& preGain = distortionChain.get<DistortionData::ChainPositions::PreGain>();
    preGain.setGainDecibels (0.0f);

    auto& postGain = distortionChain.get<DistortionData::ChainPositions::PostGain>();
    postGain.setGainDecibels (0.0f);
};

void DistortionData::prepareToPlay(double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    spec.sampleRate = sampleRate;

    updateHighpassFilter(20.f); // default value
    
    //a dsp processorChain takes to instantiate the spec
    distortionChain.prepare(spec);
    this->isPrepared = true;
}

void DistortionData::updateHighpassFilter(float highPassFreq){
    auto& filter = distortionChain.get<DistortionData::ChainPositions::Filter>();                 
    filter.state = FilterCoefs::makeFirstOrderHighPass (sampleRate, highPassFreq);
}

void DistortionData::update(juce::AudioProcessorValueTreeState& apvts){
    auto gain = apvts.getRawParameterValue("DistGain")->load();
    auto highPassFreq = apvts.getRawParameterValue("DistHighPassFreq")->load();
    auto active = apvts.getRawParameterValue("DistActive")->load();
    
    distortionChain.get<DistortionData::ChainPositions::PreGain>().setGainDecibels (gain);
    distortionChain.get<DistortionData::ChainPositions::PostGain>().setGainDecibels (-gain);
    updateHighpassFilter(highPassFreq);
    this->isActive = active;
};


void DistortionData::processBlock(juce::AudioBuffer<float> &buffer){
    if (!isActive)
        return;
    
    juce::dsp::AudioBlock<float> block(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
    distortionChain.process(context);
};

void DistortionData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    /*
     Distortion settings :
     DistPreGain => pregain  (-60 : +60 [dB])
     HighPassFreq => lowCut frequency (20 : 20000 [Hz])
     */
    layout.add(std::make_unique<juce::AudioParameterFloat>("DistGain",
                                                           "DistPreGain",
                                                           juce::NormalisableRange<float>(-60.0f, 60.f, .1f, 1.f),
                                                            0.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("DistHighPassFreq",
                                                           "DistHighPassFreq",
                                                           juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 0.25f),
                                                           1000.f));
    
    layout.add(std::make_unique<juce::AudioParameterBool>("DistActive", "DistActive", false));
};

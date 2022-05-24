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
    //Can process only one channel of audio
    spec.numChannels = 1;
    spec.sampleRate = sampleRate;
    //a dsp processorChain takes to instantiate the spec
    this->prepare(spec);

    this->isPrepared = true;
}

void DistortionData::prepareToPlay(const juce::dsp::ProcessSpec &specs){
    auto& filter = this->template get<filterIndex>();
    filter.state = FilterCoefs::makeFirstOrderHighPass (specs.sampleRate, highPassFreq);  

    this->prepare(specs);
};


void DistortionData::update(juce::AudioProcessorValueTreeState& apvts){
    this->preGain = apvts.getRawParameterValue("DistPreGain")->load();
    this->postGain = apvts.getRawParameterValue("DistPostGain")->load();
    this->highPassFreq = apvts.getRawParameterValue("DistHighPassFreq")->load();
    
    this->template get<preGainIndex>().setGainDecibels (preGain);
    this->template get<postGainIndex>().setGainDecibels (postGain);
    this->template get<filterIndex>().state = FilterCoefs::makeFirstOrderHighPass(sampleRate, highPassFreq);
};


void DistortionData::processBlock(juce::AudioBuffer<float> &buffer){
    juce::dsp::AudioBlock<float> block(buffer);
    
    for(auto i = 0; i < block.getNumChannels(); ++i)
    {
        auto monoBlock = block.getSingleChannelBlock(i);
        juce::dsp::ProcessContextReplacing<float> monoContext(monoBlock);
        this->process(monoContext);
    }
};

void DistortionData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    /*
     Distortion settings :
     DistPreGain => pregain  (-60 - 60 [dB])
     HighPassFreq => lowCut frequency (20 - 20000 [Hz])
     DistPostGain => pregain  (-60 - 60 [dB])
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


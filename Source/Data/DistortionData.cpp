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
    DistortionData::prepare(spec);

    this->isPrepared = true;
}

void DistortionData::prepareToPlay(const juce::dsp::ProcessSpec &specs){
    auto& filter = this->template get<filterIndex>();
    filter.state = FilterCoefs::makeFirstOrderHighPass (specs.sampleRate, highPassFreq);  

    this->prepare(specs);
};

void DistortionData::update(float preGain, float postGain, float highPassFreq ){
    this->preGain = preGain;
    this->postGain = postGain;
    this->highPassFreq = highPassFreq;
    
    this->template get<preGainIndex>().setGainDecibels (preGain);

    this->template get<postGainIndex>().setGainDecibels (postGain);
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



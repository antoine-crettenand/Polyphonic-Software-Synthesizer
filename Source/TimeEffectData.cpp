/*
  ==============================================================================

    TimeEffectData.cpp
    Created: 14 Jun 2022 9:57:23am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "TimeEffectData.h"
void TimeEffectData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    circularBuffer.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);

    isPrepared = true;
}

void TimeEffectData::update(juce::AudioProcessorValueTreeState& apvts){
    this->isActive = apvts.getRawParameterValue(nameID + "TimeIsActive")->load();
}

void TimeEffectData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    layout.add(std::make_unique<juce::AudioParameterBool>(nameID + "TimeIsActive",
                                                          nameID + "TimeIsActive",
                                                          false));
    
}

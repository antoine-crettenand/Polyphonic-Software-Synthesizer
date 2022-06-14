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

    oscLeft.prepare(spec);
    oscRight.prepare(spec);
    circularBuffer.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);

    isPrepared = true;
}

void TimeEffectData::update(juce::AudioProcessorValueTreeState& apvts){
    TimeSettings settings = getTimeSettings(apvts);
    oscLeft.setFrequency(settings.freq);
    oscLeft.setWaveType(settings.waveType);
    
    oscRight.setFrequency(settings.freq);
    oscRight.setWaveType(settings.waveType);
    oscRight.shift = settings.shift;
    this->isActive = settings.isActive;
}

void TimeEffectData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){

    layout.add(std::make_unique<juce::AudioParameterFloat>(nameID + "ModFreq",
                                                           nameID + "ModFreq",
                                                           juce::NormalisableRange<float>(0.3f, 30.f, 0.01f, 0.25f),
                                                            1.f));
    
    juce::StringArray waveTypeChoices = oscLeft.getWaveTypeChoices();
    layout.add(std::make_unique<juce::AudioParameterChoice>(nameID + "ModWaveType",
                                                            nameID + "ModWaveType",
                                                            waveTypeChoices, 0));
    
    layout.add(std::make_unique<juce::AudioParameterBool>(nameID + "ModIsActive",
                                                          nameID + "ModIsActive",
                                                          false));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(nameID + "ModShift",
                                                           nameID + "ModShift",
                                                           juce::NormalisableRange<float>(0.f, juce::MathConstants<float>::pi, 0.01f, 0.25f),
                                                           0));
}

TimeSettings TimeEffectData::getTimeSettings(juce::AudioProcessorValueTreeState& apvts){
    TimeSettings settings;

    settings.freq = apvts.getRawParameterValue(nameID + "ModFreq")->load();
    settings.waveType = apvts.getRawParameterValue(nameID + "ModWaveType")->load();
    settings.shift = apvts.getRawParameterValue(nameID + "ModShift")->load();
    settings.isActive = apvts.getRawParameterValue(nameID + "ModIsActive")->load();
    
    return settings;
}

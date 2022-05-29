/*
  ==============================================================================

    ModEffectData.cpp
    Created: 21 May 2022 10:00:01am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "ModEffectData.h"

void ModEffectData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    oscLeft.prepare(spec);
    oscRight.prepare(spec);

    isPrepared = true;
}

void ModEffectData::update(juce::AudioProcessorValueTreeState& apvts){
    ModSettings settings = getModSettings(apvts);
    oscLeft.setFrequency(settings.freq);
    oscLeft.setWaveType(settings.waveType);
    
    oscRight.setFrequency(settings.freq);
    oscRight.setWaveType(settings.waveType);
    oscRight.shift = settings.shift;
    this->isActive = settings.isActive;
}

void ModEffectData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){

    layout.add(std::make_unique<juce::AudioParameterFloat>(nameID + "ModFreq",
                                                           nameID + "ModFreq",
                                                           juce::NormalisableRange<float>(0.001f, 10.f, 0.01f, 0.25f),
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

ModSettings ModEffectData::getModSettings(juce::AudioProcessorValueTreeState& apvts){
    ModSettings settings;

    settings.freq = apvts.getRawParameterValue(nameID + "ModFreq")->load();
    settings.waveType = apvts.getRawParameterValue(nameID + "ModWaveType")->load();
    settings.shift = apvts.getRawParameterValue(nameID + "ModShift")->load();
    settings.isActive = apvts.getRawParameterValue(nameID + "ModIsActive")->load();
    
    return settings;
}


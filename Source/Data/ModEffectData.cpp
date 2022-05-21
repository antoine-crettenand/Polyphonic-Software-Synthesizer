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

    osc.prepare(spec);
}
void ModEffectData::processBlock(juce::AudioBuffer<float>& buffer){
    
}

void ModEffectData::update(juce::AudioProcessorValueTreeState& apvts){
    ModSettings settings = getModSettings(apvts);
    osc.setFrequency(settings.freq);
    osc.setWaveType(settings.waveType);
}

void ModEffectData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    layout.add(std::make_unique<juce::AudioParameterFloat>("ModFreq",
                                                           "ModFreq",
                                                           juce::NormalisableRange<float>(0.f, 100.f, 0.5f, 0.25f),
                                                            10.f));
    
    juce::StringArray waveTypeChoices = osc.getWaveTypeChoices();
    layout.add(std::make_unique<juce::AudioParameterChoice>("ModWaveType", "ModWaveType", waveTypeChoices, 0));
}

ModSettings ModEffectData::getModSettings(juce::AudioProcessorValueTreeState& apvts){
    ModSettings settings;

    settings.freq = apvts.getRawParameterValue("ModFreq")->load();
    settings.waveType = apvts.getRawParameterValue("ModWaveType")->load();
    return settings;
}


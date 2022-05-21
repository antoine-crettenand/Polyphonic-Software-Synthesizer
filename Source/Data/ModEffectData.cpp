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
    isPrepared = true;
}
void ModEffectData::processBlock(juce::AudioBuffer<float>& buffer){
//    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    //0 for left
    auto* leftBuffer  = buffer.getWritePointer (0);
//    auto* rightBuffer = buffer.getWritePointer (1);
   
    for (auto i = 0; i < buffer.getNumSamples(); ++i)
    {
        float level = osc.processSample(0.f);
        auto nextSample = leftBuffer[i] * level;
        
        leftBuffer[i]  = nextSample;                                          
    }

    

}

void ModEffectData::update(juce::AudioProcessorValueTreeState& apvts){
    ModSettings settings = getModSettings(apvts);
    osc.setFrequency(settings.freq);
    osc.setWaveType(settings.waveType);
}

void ModEffectData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(nameID + "ModFreq",
                                                           nameID + "ModFreq",
                                                           juce::NormalisableRange<float>(0.f, 20.f, 0.5f, 0.25f),
                                                            5.f));
    
    juce::StringArray waveTypeChoices = osc.getWaveTypeChoices();
    layout.add(std::make_unique<juce::AudioParameterChoice>(nameID + "ModWaveType",
                                                            nameID + "ModWaveType",
                                                            waveTypeChoices, 0));
}

ModSettings ModEffectData::getModSettings(juce::AudioProcessorValueTreeState& apvts){
    ModSettings settings;
    nameID + nameID;
    settings.freq = apvts.getRawParameterValue(nameID + "ModFreq")->load();
    settings.waveType = apvts.getRawParameterValue(nameID + "ModWaveType")->load();
    return settings;
}


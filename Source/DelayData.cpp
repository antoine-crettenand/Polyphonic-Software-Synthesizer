/*
  ==============================================================================

    DelayData.cpp
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "DelayData.h"

void DelayData::processBlock(juce::AudioBuffer<float>& buffer) {
    circularBuffer.processBlock(buffer, timeDelay, false);
    int bufferSize = buffer.getNumSamples();
    
    if (!isActive){
        circularBuffer.updatePointers(timeDelay, bufferSize);
        return;
    }
    auto readPointer = circularBuffer.getReadPointer();
    
    juce::AudioBuffer<float> memoryBuffer = circularBuffer.getCircularBuffer();
    int memoryBufferSize = memoryBuffer.getNumSamples();
    
    for (int channel = 0; channel < spec.numChannels; ++ channel){
        
        if(readPointer + bufferSize < memoryBufferSize){
            buffer.addFromWithRamp(channel, 0, memoryBuffer.getReadPointer(channel, readPointer), bufferSize, gainDelay, gainDelay);
        }
        else {
            auto numSamplesToEnd = memoryBufferSize - readPointer;
            buffer.addFromWithRamp(channel, 0, memoryBuffer.getReadPointer(channel, readPointer), numSamplesToEnd, gainDelay, gainDelay);
            
            auto numSamplesToStart = bufferSize - numSamplesToEnd;
            buffer.addFromWithRamp(channel, numSamplesToEnd, memoryBuffer.getReadPointer(channel, 0), numSamplesToStart, gainDelay, gainDelay);
        }
    }
    //feedback loop
    circularBuffer.processBlock(buffer, timeDelay, true);
}

void DelayData::update(juce::AudioProcessorValueTreeState& apvts){
    TimeEffectData::update(apvts);
    timeDelay = apvts.getRawParameterValue(nameID + "TimeDelay")->load();
    gainDelay = apvts.getRawParameterValue(nameID + "GainDelay")->load();
    
    
}
void DelayData::setParameterLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout){
    TimeEffectData::setParameterLayout(layout);
    layout.add(std::make_unique<juce::AudioParameterFloat>(nameID + "TimeDelay",
                                                           nameID + "TimeDelay",
                                                           juce::NormalisableRange<float>(0.3f, 3.f, 0.01f, 0.25f),
                                                            1.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(nameID + "GainDelay",
                                                           nameID + "GainDelay",
                                                           juce::NormalisableRange<float>(0.0f, 1.f, 0.01f, 0.25f),
                                                            0.8f));
    
}

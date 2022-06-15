/*
  ==============================================================================

    DelayData.cpp
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "DelayData.h"

void DelayData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    TimeEffectData::prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    //    juce::AudioBuffer<float> initBuffer = juce::AudioBuffer(buffer);
    delayBuffer = juce::AudioBuffer<float>(outputChannels, samplesPerBlock);
    
}

void DelayData::processBlock(juce::AudioBuffer<float>& buffer) {

    
    circularBuffer.processBlock(buffer, timeDelay, false);
    int bufferSize = buffer.getNumSamples();
    
    if (!isActive){
        circularBuffer.updatePointers(timeDelay, bufferSize);
        return;
    }
    
    fillDelayBuffer(buffer);
    
    //feedback loop
    circularBuffer.processBlock(buffer, timeDelay, true);
}

void DelayData::fillDelayBuffer(juce::AudioBuffer<float>& delayBuffer){
    juce::AudioBuffer<float> memoryBuffer = circularBuffer.getCircularBuffer();
    int memoryBufferSize = memoryBuffer.getNumSamples();

    auto bufferSize = delayBuffer.getNumSamples();
    auto readPointer = circularBuffer.getReadPointer();
    
    for (int channel = 0; channel < spec.numChannels; ++ channel){

        if(readPointer + bufferSize < memoryBufferSize){
            delayBuffer.addFromWithRamp(channel, 0, memoryBuffer.getReadPointer(channel, readPointer), bufferSize, gainDelay, gainDelay);
        }
        else {
            auto numSamplesToEnd = memoryBufferSize - readPointer;
            delayBuffer.addFromWithRamp(channel, 0, memoryBuffer.getReadPointer(channel, readPointer), numSamplesToEnd, gainDelay, gainDelay);
        
            auto numSamplesToStart = bufferSize - numSamplesToEnd;
            delayBuffer.addFromWithRamp(channel, numSamplesToEnd, memoryBuffer.getReadPointer(channel, 0), numSamplesToStart, gainDelay, gainDelay);
        }
    }
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
                                                           juce::NormalisableRange<float>(0.01f, 1.f, 0.01f, 0.5f),
                                                            0.22f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(nameID + "GainDelay",
                                                           nameID + "GainDelay",
                                                           juce::NormalisableRange<float>(0.0f, 1.f, 0.01f, 0.6f),
                                                            0.42f));
    
}

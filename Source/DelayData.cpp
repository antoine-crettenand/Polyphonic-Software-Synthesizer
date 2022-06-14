/*
  ==============================================================================

    DelayData.cpp
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "DelayData.h"

void DelayData::processBlock(juce::AudioBuffer<float>& buffer) {
    circularBuffer.processBlock(buffer, delayTime);
    
    if (!isActive){
        return;
    }
    auto readPointer = circularBuffer.getReadPointer();
    int bufferSize = buffer.getNumSamples();
    juce::AudioBuffer<float> memoryBuffer = circularBuffer.getCircularBuffer();
    int memoryBufferSize = memoryBuffer.getNumSamples();
    
    for (int channel = 0; channel < spec.numChannels; ++ channel){
        if(readPointer + bufferSize < memoryBufferSize){
            float gainDelay = 0.3f;
            buffer.addFromWithRamp(channel, 0, memoryBuffer.getReadPointer(channel, readPointer), bufferSize, gainDelay, gainDelay);
        }
        else {
            auto numSamplesToEnd = memoryBufferSize - readPointer;
            float gainDelay = 0.3f;
            buffer.addFromWithRamp(channel, 0, memoryBuffer.getReadPointer(channel, readPointer), numSamplesToEnd, gainDelay, gainDelay);
            
            auto numSamplesToStart = bufferSize - numSamplesToEnd;
            buffer.addFromWithRamp(channel, numSamplesToEnd, memoryBuffer.getReadPointer(channel, 0), numSamplesToStart, gainDelay, gainDelay);
        }
    }
}

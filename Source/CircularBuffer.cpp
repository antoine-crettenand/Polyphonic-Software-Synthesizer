/*
  ==============================================================================

    CircularBuffer.cpp
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "CircularBuffer.h"

void CircularBuffer::prepareToPlay(double sampleRate, int samplesPerBlock, int outputNumChannels){
    auto circularBufferSize = static_cast<int>(sampleRate * maxTimeDelay);
    sample_rate = sampleRate;
    numChannels = outputNumChannels;
    circularBuffer.setSize(numChannels, circularBufferSize);
    isInit = true;
}

void CircularBuffer::processBlock(juce::AudioBuffer<float>& buffer, float timeDelay){
    assert(isInit);
    
    auto bufferSize = buffer.getNumSamples();
    auto circularBufferSize = circularBuffer.getNumSamples();
    
    for (int channel = 0; channel < numChannels; ++ channel){
        auto* channelData = buffer.getWritePointer(channel);
        
        int remainSamples = circularBufferSize - writePointer;
        
        if (remainSamples > bufferSize){
            circularBuffer.copyFromWithRamp(channel, writePointer, channelData, bufferSize, 1.f,1.f);
        }
        else {
            
            circularBuffer.copyFromWithRamp(channel, writePointer, channelData, remainSamples, 1.f, 1.f);
            int numSamplesStart = bufferSize - remainSamples;
            circularBuffer.copyFromWithRamp(channel, 0, channelData + remainSamples, numSamplesStart, 1.f, 1.f);
        }
        updateReadPointer(timeDelay, bufferSize, circularBufferSize);
    }
    writePointer += bufferSize;
    writePointer %= circularBufferSize;
}


int CircularBuffer::getWritePointer(){
    return writePointer;
}

int CircularBuffer::getReadPointer(){
    return readPointer;
}

juce::AudioBuffer<float> CircularBuffer::getCircularBuffer(){
    return circularBuffer;
}

void CircularBuffer::updateReadPointer(int sec, int bufferSize, int circularBufferSize){
    assert(sec < maxTimeDelay);
    readPointer = static_cast<int>(writePointer - sec * sample_rate);
    if (readPointer < 0){
        readPointer += circularBufferSize;
    }
}

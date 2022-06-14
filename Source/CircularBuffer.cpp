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

void CircularBuffer::processBlock(juce::AudioBuffer<float>& buffer, float timeDelay, bool update){
    assert(isInit);
    
    auto bufferSize = buffer.getNumSamples();
    
    for (int channel = 0; channel < numChannels; ++ channel){
        fillBuffer(buffer, channel);
    }
    if(update){
        updatePointers(timeDelay, bufferSize);
    }
}

void CircularBuffer::fillBuffer(juce::AudioBuffer<float>& buffer, int channel){
    auto* channelData = buffer.getWritePointer(channel);
    auto bufferSize = buffer.getNumSamples();
    auto circularBufferSize = circularBuffer.getNumSamples();
    
    int remainSamples = circularBufferSize - writePointer;
    
    if (remainSamples > bufferSize){
        circularBuffer.copyFromWithRamp(channel, writePointer, channelData, bufferSize, 1.f,1.f);
    }
    else {
        circularBuffer.copyFromWithRamp(channel, writePointer, channelData, remainSamples, 1.f, 1.f);
        int numSamplesStart = bufferSize - remainSamples;
        circularBuffer.copyFromWithRamp(channel, 0, channelData + remainSamples, numSamplesStart, 1.f, 1.f);
    }
    
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

void CircularBuffer::updateWritePointer(int bufferSize){
    writePointer += bufferSize;
    writePointer %= circularBuffer.getNumSamples();
}

void CircularBuffer::updateReadPointer(int sec, int bufferSize){
    assert(sec < maxTimeDelay);
    readPointer = static_cast<int>(writePointer - sec * sample_rate);
    if (readPointer < 0){
        readPointer += circularBuffer.getNumSamples();
    }
}
                       
void CircularBuffer::updatePointers(int sec, int bufferSize){
    updateWritePointer(bufferSize);
    updateReadPointer(sec, bufferSize);
}


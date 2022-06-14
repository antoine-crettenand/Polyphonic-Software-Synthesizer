/*
  ==============================================================================

    CircularBuffer.cpp
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "CircularBuffer.h"

void CircularBuffer::prepareToPlay(double sampleRate, int samplesPerBlock, int outputNumChannels){
//TODO : fixed size to variable ??
    auto circularBufferSize = sampleRate * 2.0;
    numChannels = outputNumChannels;
    circularBuffer.setSize(numChannels, (int)circularBufferSize);
}

void CircularBuffer::processBlock(juce::AudioBuffer<float>& buffer){
    auto bufferSize = buffer.getNumSamples();
    auto circularBufferSize = circularBuffer.getNumSamples();
    
    for (int channel = 0; channel < numChannels; ++ channel){
        auto* channelData = buffer.getWritePointer(channel);
        
        int remainSamples = circularBufferSize - writePointer;
        
        if (remainSamples > bufferSize){
            circularBuffer.copyFromWithRamp(channel, writePointer, channelData, bufferSize, 0.1f, 0.1f);
        }
        else {
            int numSamplesStart = bufferSize - remainSamples;
            circularBuffer.copyFromWithRamp(channel, writePointer, channelData, remainSamples, 0.1f, 0.1f);
            //TODO : check channel data
            circularBuffer.copyFromWithRamp(channel, 0, channelData + remainSamples, numSamplesStart, 0.1f, 0.1f);
            
        }
    }
    writePointer += bufferSize;
    writePointer %= circularBufferSize;
}

/*
  ==============================================================================

    CircularBuffer.h
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CircularBuffer
{
public :
    CircularBuffer()
    {
    }
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputNumChannels);
    void processBlock(juce::AudioBuffer<float>& buffer);
    

private :
    juce::AudioBuffer<float> circularBuffer;
    int writePointer = 0;
    int numChannels = 2;
};

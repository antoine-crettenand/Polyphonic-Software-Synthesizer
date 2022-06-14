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
    CircularBuffer(float maxTimeDelay):maxTimeDelay(maxTimeDelay)
    {
    }
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputNumChannels);
    void processBlock(juce::AudioBuffer<float>& buffer, float timeDelay, bool update);
    int getWritePointer();
    int getReadPointer();
    juce::AudioBuffer<float> getCircularBuffer();
    
    void fillBuffer(juce::AudioBuffer<float>& buffer, int channel);
    void updatePointers(int sec, int bufferSize);
    
    
private :
    void updateReadPointer(int sec, int bufferSize);
    void updateWritePointer(int bufferSize);
    juce::AudioBuffer<float> circularBuffer;
    int writePointer = 0;
    int readPointer = 0;
    int numChannels = 2;
    int sample_rate;
    float maxTimeDelay;
    bool isInit = false;
};

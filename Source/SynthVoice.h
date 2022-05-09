/*
  ==============================================================================

    SynthVoice.h
    Created: 2 May 2022 10:00:55am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
# include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound *sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    //use lambda function, another : ;
    juce::dsp::Oscillator<float> osc {[](float x){ return std::sin(x); }};
    
    juce::AudioBuffer<float> synthBuffer;
    /*
     sin wave : return std::sin(x)
     square wave : return x < 0.0f ? -1.0f : 1.0f;
     saw wave : return x / juce::MathConstants<float>::pi; (scie /|/|)
     => more efficient when change freq : use lookup table
     */
    juce::dsp::Gain<float> gain;
    //to enforce to use prepareToPlay
    bool isPrepared { false };
    
    
};

/*
  ==============================================================================

    SynthVoice.h
    Created: 2 May 2022 10:00:55am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/LFOData.h"

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
    
    void update(juce::AudioProcessorValueTreeState& apvts);
    OscData& getOscillator() { return osc; };
    LFOData& getLFO() { return lfo; };

private:
    AdsrData ampAdsr;
    //use lambda function, another : ;
    OscData osc;
    
    LFOData lfo;
    
    juce::AudioBuffer<float> synthBuffer;
    juce::dsp::Gain<float> gain;
    //to enforce to use prepareToPlay
    bool isPrepared { false };
};
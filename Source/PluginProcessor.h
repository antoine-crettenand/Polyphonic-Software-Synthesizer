/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"

struct AmpSettings {
    float gain {0}, attack {0}, decay {0}, sustain {0}, release {0};
};

AmpSettings getAmpSettings(juce::AudioProcessorValueTreeState& apvts);

//==============================================================================
/**
*/
class COM418AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    COM418AudioProcessor();
    ~COM418AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(int numberOscillators);
    juce::AudioProcessorValueTreeState apvts;

private:
    juce::Synthesiser synth;
    const int NUMBER_OSCILLATORS = 3; // If modified, also needs to change call to createParameterLayout since NUMBER_OSCILLATORS is instantiated afterwards
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (COM418AudioProcessor)
};

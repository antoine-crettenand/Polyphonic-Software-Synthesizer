/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"
#include "Synth.h"
#include "Data/FilterData.h"
#include "Data/DistortionData.h"
#include "Data/TremoloData.h"
#include "Data/DelayData.h"
#include "UI/WaveformVisualizerComponent.h"


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
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(int numberOscs);
    juce::AudioProcessorValueTreeState apvts;
    WaveformVisualizerComponent waveformVisualizer;

private:
    Synth synth;
    int numberOscillators; //Is set in createParameterLayout because we need it in this method (before the constructor)
    int numberPolyphony = 7;
    FilterData* filter; // = new FilterData();
    DistortionData* distortion;
    TremoloData* tremoloEffect;// = new ModEffectData("modEffect");
    DelayData* delayEffect;

    juce::dsp::Gain<float> masterGain;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (COM418AudioProcessor)
    
};

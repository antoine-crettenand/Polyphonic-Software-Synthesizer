/*
  ==============================================================================

    OscComponent.cpp
    Created: 10 May 2022 2:18:03am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices = {"Sine", "Saw", "Square"};
    oscWaveTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveTypeSelector);
    
    oscWaveTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveTypeSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    oscWaveTypeSelector.setBounds(0, 0, 90, 20);
}

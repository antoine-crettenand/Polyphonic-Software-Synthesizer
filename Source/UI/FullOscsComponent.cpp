/*
  ==============================================================================

    FullOscsComponent.cpp
    Created: 16 May 2022 12:07:33pm
    Author:  Loïc

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FullOscsComponent.h"

//==============================================================================
FullOscsComponent::FullOscsComponent(juce::AudioProcessorValueTreeState& apvts, int numberOscillators)
{

    for (int i = 0; i < numberOscillators; ++i) {
        OscComponent* osc = new OscComponent(apvts, i);
        oscs.push_back(osc);
        addAndMakeVisible(*osc);
    }

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    frequencyText.setText("Frequency", juce::dontSendNotification);
    waveformText.setText("Waveform", juce::dontSendNotification);
    volumeText.setText("Volume", juce::dontSendNotification);
    oSCText.setButtonText("OSC");

    oSCText.setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);

    addAndMakeVisible(frequencyText);
    addAndMakeVisible(waveformText);
    addAndMakeVisible(volumeText);
    addAndMakeVisible(oSCText);
}

FullOscsComponent::~FullOscsComponent()
{
}

void FullOscsComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void FullOscsComponent::resized()
{
    const auto elementWidth = getWidth() / 6;
    const auto padding = getWidth() / 15;

    const double HEIGHT_MARGIN = getHeight() / 30;

    const size_t NUMBER_OSCILLATORS = oscs.size();

    oSCText.setBounds(padding, HEIGHT_MARGIN, getWidth() / 6, getHeight() / 6);
    frequencyText.setBounds(oSCText.getRight()+padding, HEIGHT_MARGIN, elementWidth, getHeight() / 12);
    waveformText.setBounds(frequencyText.getRight() + padding, HEIGHT_MARGIN, elementWidth, getHeight() / 12);
    volumeText.setBounds(waveformText.getRight() + padding, HEIGHT_MARGIN, elementWidth, getHeight() / 12);


    double usedHeight = getHeight()/6 + HEIGHT_MARGIN;
    double remainingHeight = 5*getHeight()/6;

    for (size_t i = 0; i < NUMBER_OSCILLATORS; ++i) {
        oscs[i]->setBounds(0, i * remainingHeight/NUMBER_OSCILLATORS + usedHeight, getWidth(), remainingHeight / NUMBER_OSCILLATORS);
    }
}

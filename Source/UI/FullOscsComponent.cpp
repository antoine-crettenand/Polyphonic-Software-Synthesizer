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
FullOscsComponent::FullOscsComponent(juce::AudioProcessorValueTreeState& apvts) : oscComponent1(apvts, 0), oscComponent2(apvts, 1), oscComponent3(apvts, 2)
{

    addAndMakeVisible(oscComponent1);
    addAndMakeVisible(oscComponent2);
    addAndMakeVisible(oscComponent3);

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    frequencyText.setButtonText("Frequency");
    waveformText.setButtonText("Waveform");
    volumeText.setButtonText("Volume");
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
    const auto bounds = getLocalBounds();

    const double WIDTH_UNUSED_SPACE = bounds.getWidth() / 26;
    const double HEIGHT_MARGIN = bounds.getHeight() / 30;

    oscComponent1.setBounds(0, bounds.getHeight() / 4, bounds.getWidth(), bounds.getHeight() / 4);
    oscComponent2.setBounds(0, 2*bounds.getHeight() / 4, bounds.getWidth(), bounds.getHeight() / 4);
    oscComponent3.setBounds(0, 3*bounds.getHeight() / 4, bounds.getWidth(), bounds.getHeight() / 4);

    frequencyText.setBounds(bounds.getWidth()/4 + WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth()/4-2* WIDTH_UNUSED_SPACE, bounds.getHeight() / 12);
    waveformText.setBounds(2*bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 12);
    volumeText.setBounds(3*bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 12);

    oSCText.setBounds(WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 6);
}

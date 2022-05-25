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

    const size_t NUMBER_OSCILLATORS = oscs.size();


    frequencyText.setBounds(bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 12);
    waveformText.setBounds(2 * bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 12);
    volumeText.setBounds(3 * bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 12);

    oSCText.setBounds(WIDTH_UNUSED_SPACE, HEIGHT_MARGIN, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 6);

    double usedHeight = bounds.getHeight()/6 + 3*HEIGHT_MARGIN; //3 to let some space

    double remainingHeight = bounds.getHeight()-usedHeight;

    for (size_t i = 0; i < NUMBER_OSCILLATORS; ++i) {
        oscs[i]->setBounds(0, i * remainingHeight/NUMBER_OSCILLATORS + usedHeight, bounds.getWidth(), remainingHeight / NUMBER_OSCILLATORS);
    }
}

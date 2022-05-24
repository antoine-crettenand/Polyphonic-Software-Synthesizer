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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, int oscNumber)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    oscText.setButtonText("Osc " + std::to_string(oscNumber+1));
    addAndMakeVisible(oscText);

    freq.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    freq.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(freq);
    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "Freq" + std::to_string(oscNumber), freq);

    juce::StringArray choices = { "Sine", "Saw", "Square" };
    oscWaveTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveTypeSelector);
    oscWaveTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "Osc" + std::to_string(oscNumber) + "WaveType", oscWaveTypeSelector);

    volume.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volume.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(volume);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "Volume" + std::to_string(oscNumber), volume);

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

    const auto bounds = getLocalBounds();

    const double WIDTH_UNUSED_SPACE = bounds.getWidth() / 26;

    oscText.setBounds(bounds.getWidth() / 16, 0, bounds.getWidth() / 8, bounds.getHeight()/3);
    freq.setBounds(bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, 0, bounds.getWidth() / 4 - 2* WIDTH_UNUSED_SPACE, 2 * bounds.getHeight() / 3);
    oscWaveTypeSelector.setBounds(2*bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, 0, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 3);
    volume.setBounds(3*bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, 0, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, 2 * bounds.getHeight() / 3);
}

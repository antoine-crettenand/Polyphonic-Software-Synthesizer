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
    // initialise any special settings that your component needs.$
    oscText.setText("Osc" + std::to_string(oscNumber + 1), juce::dontSendNotification);
    addAndMakeVisible(oscText);

    freq.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    freq.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    freq.setTextValueSuffix(" semitones");
    addAndMakeVisible(freq);
    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "Freq" + std::to_string(oscNumber), freq);

    juce::StringArray choices = { "Sine", "Saw", "Square" };
    oscWaveTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveTypeSelector);
    oscWaveTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "Osc" + std::to_string(oscNumber) + "WaveType", oscWaveTypeSelector);

    volume.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volume.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    volume.setTextValueSuffix(" dB");
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
    const auto elementWidth = getWidth() / 6;
    const auto padding = getWidth() / 15;
    const auto heightMargin = getHeight() / 6;

    oscText.setBounds(padding, heightMargin, getWidth()/6, getHeight() / 3);
    freq.setBounds(oscText.getRight()+padding, heightMargin/3, elementWidth, 2 * getHeight() / 3);
    oscWaveTypeSelector.setBounds(freq.getRight() + padding, heightMargin, elementWidth, getHeight() / 3);
    volume.setBounds(oscWaveTypeSelector.getRight() + padding, heightMargin/3, elementWidth, 2 * getHeight() / 3);
}

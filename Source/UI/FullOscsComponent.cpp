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
FullOscsComponent::FullOscsComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    frequencyText.setButtonText("Frequency");
    waveformText.setButtonText("Waveform");
    volumeText.setButtonText("Volume");
    osc1Text.setButtonText("Osc 1");
    osc2Text.setButtonText("Osc 2");
    osc3Text.setButtonText("Osc 3");
    oSCText.setButtonText("OSC");
    

    juce::StringArray choices = { "Sine", "Saw", "Square" };
    oscWaveTypeSelector1.addItemList(choices, 1);
    addAndMakeVisible(oscWaveTypeSelector1);
    oscWaveTypeSelector2.addItemList(choices, 1);
    addAndMakeVisible(oscWaveTypeSelector2);
    oscWaveTypeSelector3.addItemList(choices, 1);
    addAndMakeVisible(oscWaveTypeSelector3);

    
    freq1.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    freq2.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    freq3.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    freq1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    freq2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    freq3.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    vol1.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    vol2.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    vol3.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    vol1.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    vol2.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    vol3.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    oSCText.setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);
    //osc1Text.setColour(juce::TextButton::textColourOnId, juce::Colours::green);
    //osc1Text.setColour(juce::TextButton::buttonColourId, juce::Colours::blue);
    //osc1Text.setColour(juce::TextButton::buttonNormal, juce::Colours::purple);

    //if (osc1Text.isMouseOver()) {
    //    osc1Text.setColour(juce::TextButton::textColourOffId, juce::Colours::purple);
    //}



    addAndMakeVisible(frequencyText);
    addAndMakeVisible(waveformText);
    addAndMakeVisible(volumeText);
    addAndMakeVisible(osc1Text);
    addAndMakeVisible(osc2Text);
    addAndMakeVisible(osc3Text);
    addAndMakeVisible(oSCText);


    addAndMakeVisible(freq1);
    addAndMakeVisible(freq2);
    addAndMakeVisible(freq3);

    addAndMakeVisible(vol1);
    addAndMakeVisible(vol2);
    addAndMakeVisible(vol3);

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
    osc1Text.setBounds(25, 75, 50, 25);
    osc2Text.setBounds(25, 150, 50, 25);
    osc3Text.setBounds(25, 225, 50, 25);
    oSCText.setBounds(15, 10, 70, 50);

    frequencyText.setBounds(115, 10, 70, 25);
    waveformText.setBounds(215, 10, 70, 25);
    volumeText.setBounds(315, 10, 70, 25);

    freq1.setBounds(115, 63, 70, 50);
    freq2.setBounds(115, 138, 70, 50);
    freq3.setBounds(115, 213, 70, 50);

    oscWaveTypeSelector1.setBounds(215, 75, 70, 25);
    oscWaveTypeSelector2.setBounds(215, 150, 70, 25);
    oscWaveTypeSelector3.setBounds(215, 225, 70, 25);

    vol1.setBounds(315, 63, 70, 50);
    vol2.setBounds(315, 138, 70, 50);
    vol3.setBounds(315, 213, 70, 50);


}

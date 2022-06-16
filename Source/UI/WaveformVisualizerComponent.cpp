/*
  ==============================================================================

    WaveformVisualizerComponent.cpp
    Created: 4 Jun 2022 4:08:06pm
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformVisualizerComponent.h"

//==============================================================================
WaveformVisualizerComponent::WaveformVisualizerComponent(int numChannels, juce::AudioProcessorValueTreeState& apvts) : juce::AudioVisualiserComponent(numChannels)
{
    setRepaintRate(120);
    setBufferSize(32);
    
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "MasterGain", gainSlider);
    
    gainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(gainSlider);
    
    addAndMakeVisible(gainLabel);
    gainLabel.setText ("Master Gain", juce::dontSendNotification);
    gainLabel.attachToComponent (&gainSlider, false);
    
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 50, 25);
}

WaveformVisualizerComponent::~WaveformVisualizerComponent()
{
}

void WaveformVisualizerComponent::resized() {
    auto bounds = getLocalBounds();
    const auto padding = getWidth() / 15;
    const auto labelWidth = 50;
    
    gainSlider.setBounds(padding, 0,bounds.getWidth() - 2 * padding - labelWidth, bounds.getHeight()-2);
    gainLabel.setBounds(gainSlider.getRight(), 0, labelWidth, bounds.getHeight()-2);
}


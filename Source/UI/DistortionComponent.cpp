/*
  ==============================================================================

    DistortionComponent.cpp
    Created: 28 May 2022 3:12:29am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    isActiveAttachment = std::make_unique<ButtonAttachment>(apvts, "DistActive", isActiveButton);
    gainAttachment = std::make_unique<SliderAttachment>(apvts, "DistGain", gainSlider);
    highPassFreqAttachment = std::make_unique<SliderAttachment>(apvts, "DistHighPassFreq", highPassFreqSlider);

    setParameterStyle(gainSlider);
    gainSlider.setTextValueSuffix(" dB");
    
    addAndMakeVisible(gainLabel);
    gainLabel.setText ("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent (&gainSlider, false);
    
    
    setParameterStyle(highPassFreqSlider);
    highPassFreqSlider.setTextValueSuffix(" Hz");
    
    addAndMakeVisible(highPassFreqLabel);
    highPassFreqLabel.setText("HP Frequency", juce::dontSendNotification);
    highPassFreqLabel.attachToComponent(&highPassFreqSlider, false);
    
    addAndMakeVisible(isActiveButton);
    addAndMakeVisible(isActiveLabel);
    isActiveLabel.setText("Distortion", juce::dontSendNotification);
}

void DistortionComponent::setParameterStyle(juce::Slider& slider){
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void DistortionComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto bounds = getLocalBounds().reduced(10);
    const auto labelHeight = 10;
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 3 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;
    
    isActiveButton.setBounds(padding, padding, sliderWidth, sliderHeight / 10);
    
    isActiveLabel.setBounds(padding, isActiveButton.getBottom() + padding, isActiveButton.getWidth(), labelHeight);
    
    gainSlider.setBounds(isActiveButton.getRight() + padding, sliderStartY, sliderWidth, sliderHeight - labelHeight);
    gainLabel.setBounds(isActiveButton.getRight() + padding + gainSlider.getWidth() / 4, gainSlider.getBottom() + padding, gainSlider.getWidth() / 2, labelHeight);
    highPassFreqSlider.setBounds(gainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight - labelHeight);
    highPassFreqLabel.setBounds(gainSlider.getRight() + padding, highPassFreqSlider.getBottom() + padding, highPassFreqSlider.getWidth(), labelHeight);
    }

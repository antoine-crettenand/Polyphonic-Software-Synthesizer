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

    distortionTitle.setButtonText("Distortion");
    distortionTitle.setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);
    addAndMakeVisible(distortionTitle);
    
    addAndMakeVisible(gainLabel);
    gainLabel.setText ("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent (&gainSlider, false);
    
    
    setParameterStyle(highPassFreqSlider);
    highPassFreqSlider.setTextValueSuffix(" Hz");
    
    addAndMakeVisible(highPassFreqLabel);
    highPassFreqLabel.setText("HP Frequency", juce::dontSendNotification);
    highPassFreqLabel.attachToComponent(&highPassFreqSlider, false);
    
    addAndMakeVisible(isActiveButton);
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
    const auto sliderWidth = 3*getWidth() / 10;
    const auto sliderHeight = 3 * getHeight() / 5;
    const int paddingTextVertical = getHeight() / 25;
    const int textHeight = 3 * getHeight() / 25;

    const auto paddingTitle = getWidth() / 36;
    const auto modIsActiveButtonWidth = getWidth() / 6;
    const auto paddingHorizontal = getWidth() / 10;

    isActiveButton.setBounds(getWidth() / 15, getHeight() / 10, modIsActiveButtonWidth, getHeight() / 10);
    distortionTitle.setBounds(isActiveButton.getRight() + getWidth()/25, getHeight() / 10, getWidth() / 2, getHeight() / 10);

    gainSlider.setBounds(3 * getWidth() / 20, distortionTitle.getBottom() + paddingTitle, sliderWidth, sliderHeight);
    gainLabel.setBounds(3 * getWidth() / 17, gainSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    highPassFreqSlider.setBounds(gainSlider.getRight() + paddingHorizontal, distortionTitle.getBottom() + paddingTitle, sliderWidth, sliderHeight);
    highPassFreqLabel.setBounds(gainSlider.getRight() + 2*paddingHorizontal/3, highPassFreqSlider.getBottom() + paddingTextVertical, 3*sliderWidth /2, textHeight);
   }

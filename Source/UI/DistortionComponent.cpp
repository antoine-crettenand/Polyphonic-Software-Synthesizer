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
    
    preGainAttachment = std::make_unique<SliderAttachment>(apvts, "DistPreGain", preGainSlider);
    postGainAttachment = std::make_unique<SliderAttachment>(apvts, "DistPostGain", postGainSlider);
    highPassFreqAttachment = std::make_unique<SliderAttachment>(apvts, "DistHighPassFreq", highPassFreqSlider);

    setParameterStyle(preGainSlider);
    setParameterStyle(postGainSlider);
    setParameterStyle(highPassFreqSlider);
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
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;
    
    preGainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    highPassFreqSlider.setBounds(preGainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    postGainSlider.setBounds(highPassFreqSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

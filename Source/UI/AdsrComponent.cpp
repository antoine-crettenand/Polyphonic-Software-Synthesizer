/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 10 May 2022 12:58:00am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String adsrID) : adsrID(adsrID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Attack"), attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Decay"), decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Sustain"), sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Release"), releaseSlider);

    setParameterStyle(attackSlider);
    attackSlider.setTextValueSuffix(" s.");
    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack", juce::dontSendNotification);
    
    setParameterStyle(decaySlider);
    decaySlider.setTextValueSuffix(" s.");
    addAndMakeVisible(decayLabel);
    decayLabel.setText("Decay", juce::dontSendNotification);
    
    setParameterStyle(sustainSlider);
    addAndMakeVisible(sustainLabel);
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    
    setParameterStyle(releaseSlider);
    releaseSlider.setTextValueSuffix(" s.");
    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release", juce::dontSendNotification);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto labelHeight = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - labelHeight;
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds(sliderStartX, attackSlider.getBottom() + padding, attackSlider.getWidth(), labelHeight);
    
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds(attackSlider.getRight() + padding, decaySlider.getBottom() + padding, decaySlider.getWidth(), labelHeight);
    
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds(decaySlider.getRight() + padding, sustainSlider.getBottom() + padding, sustainSlider.getWidth(), labelHeight);
    
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds(sustainSlider.getRight() + padding, releaseSlider.getBottom() + padding, releaseSlider.getWidth(), labelHeight);
}

void AdsrComponent::setParameterStyle(juce::Slider& slider){
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

// @TODO find a cleaner way of retrieving attachment keywords from apvts
juce::String AdsrComponent::getStringParameter(juce::String pName){
    return adsrID + pName;
}

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
    
    ampAttackAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Attack"), ampAttackSlider);
    ampDecayAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Decay"), ampDecaySlider);
    ampSustainAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Sustain"), ampSustainSlider);
    ampReleaseAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("Release"), ampReleaseSlider);

    setParameterStyle(ampAttackSlider);
    setParameterStyle(ampDecaySlider);
    setParameterStyle(ampSustainSlider);
    setParameterStyle(ampReleaseSlider);
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
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;
    
    ampAttackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    ampDecaySlider.setBounds(ampAttackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    ampSustainSlider.setBounds(ampDecaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    ampReleaseSlider.setBounds(ampSustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
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

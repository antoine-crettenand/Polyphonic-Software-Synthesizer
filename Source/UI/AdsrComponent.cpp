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

    adsrTitle.setButtonText("ADSR");
    adsrTitle.setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);
    addAndMakeVisible(adsrTitle);

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
    const auto sliderWidth = getWidth() / 5;
    const auto sliderHeight = 3 * getHeight() / 5;
    const int padding = getWidth() / 30;
    const int paddingTextVertical = getHeight() / 25;
    const int textHeight = 3 * getHeight() / 25;

    adsrTitle.setBounds(2 * getWidth() / 5, getHeight() / 10, getWidth() / 5, getHeight() / 10);

    attackSlider.setBounds(padding, adsrTitle.getBottom() + padding, sliderWidth, sliderHeight);
    attackLabel.setBounds(padding, attackSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, adsrTitle.getBottom() + padding, sliderWidth, sliderHeight);
    decayLabel.setBounds(attackLabel.getRight() + padding, decaySlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, adsrTitle.getBottom() + padding, sliderWidth, sliderHeight);
    sustainLabel.setBounds(decayLabel.getRight() + padding, sustainSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, adsrTitle.getBottom() + padding, sliderWidth, sliderHeight);
    releaseLabel.setBounds(sustainLabel.getRight() + padding, releaseSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);

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

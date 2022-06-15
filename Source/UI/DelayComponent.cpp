/*
  ==============================================================================

    DelayComponent.cpp
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "DelayComponent.h"
using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& apvts, juce::String nameID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    std::string name = nameID.toStdString();
    name[0] = toupper(name[0]);
    modelEffectTitle.setButtonText(name);
    modelEffectTitle.setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);
    addAndMakeVisible(modelEffectTitle);


    addAndMakeVisible(delayIsActiveButton);
    delayIsActiveAttachment = std::make_unique<ButtonAttachment>(apvts, nameID + "TimeIsActive", delayIsActiveButton);


    
    timeDelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    timeDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(timeDelaySlider);
    timeDelayAttachment = std::make_unique<SliderAttachment>(apvts, nameID + "TimeDelay", timeDelaySlider);
    timeDelayText.setText("Time", juce::dontSendNotification);
    addAndMakeVisible(timeDelayText);


    gainDelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(gainDelaySlider);
    gainDelayAttachment = std::make_unique<SliderAttachment>(apvts, nameID + "GainDelay", gainDelaySlider);
    gainDelayText.setText("Feedback", juce::dontSendNotification);
    addAndMakeVisible(gainDelayText);

}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void DelayComponent::resized()
{

    const auto sliderWidth = 9 * getWidth() / 36;
    const auto sliderHeight = 3 * getHeight() / 5;
    const int paddingTextVertical = getHeight() / 25;
    const int textHeight = 3 * getHeight() / 25;

    const auto paddingTitle = getWidth() / 36;
    const auto delayIsActiveButtonWidth = getWidth() / 6;
    const auto paddingHorizontal = getWidth() / 18 + 10;

    delayIsActiveButton.setBounds(getWidth() / 15, getHeight() / 10, delayIsActiveButtonWidth, getHeight() / 10);
    modelEffectTitle.setBounds(delayIsActiveButton.getRight() + getWidth()/24, getHeight() / 10, getWidth() / 2, getHeight() / 10);
    
    timeDelaySlider.setBounds(4 * getWidth() / 20, modelEffectTitle.getBottom() + paddingTitle, sliderWidth, sliderHeight);
    timeDelayText.setBounds(4 * getWidth() / 20, timeDelaySlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    
    gainDelaySlider.setBounds(timeDelaySlider.getRight() + paddingHorizontal, modelEffectTitle.getBottom() + paddingTitle, sliderWidth, sliderHeight);
    gainDelayText.setBounds(timeDelaySlider.getRight() + 2*paddingHorizontal/3, gainDelaySlider.getBottom() + paddingTextVertical, 3*sliderWidth /2, textHeight);

}

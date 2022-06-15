/*
  ==============================================================================

    ModEffectComponent.cpp
    Created: 26 May 2022 10:24:05am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "ModEffectComponent.h"
using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

ModEffectComponent::ModEffectComponent(juce::AudioProcessorValueTreeState& apvts, juce::String nameID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    std::string name = nameID.toStdString();
    name[0] = toupper(name[0]);
    modelEffectTitle.setButtonText(name);
    modelEffectTitle.setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);
    addAndMakeVisible(modelEffectTitle);


    addAndMakeVisible(modIsActiveButton);
    modIsActiveAttachment = std::make_unique<ButtonAttachment>(apvts, nameID + "ModIsActive", modIsActiveButton);

    modFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(modFreqSlider);
    modFreqAttachment = std::make_unique<SliderAttachment>(apvts, nameID + "ModFreq", modFreqSlider);
    modFreqText.setText("Frequency", juce::dontSendNotification);
    addAndMakeVisible(modFreqText);

    
    modShiftSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modShiftSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(modShiftSlider);
    modShiftAttachment = std::make_unique<SliderAttachment>(apvts, nameID + "ModShift", modShiftSlider);
    modShiftText.setText("Shift", juce::dontSendNotification);
    addAndMakeVisible(modShiftText);



    juce::StringArray choices = { "Sine", "Saw", "Square" };
    modWaveTypeBox.addItemList(choices, 1);
    addAndMakeVisible(modWaveTypeBox);
    modWaveTypeAttachment = std::make_unique<ComboBoxAttachment>(apvts, nameID + "ModWaveType", modWaveTypeBox);


}

ModEffectComponent::~ModEffectComponent()
{
}

void ModEffectComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void ModEffectComponent::resized()
{

    const auto sliderWidth = 9 * getWidth() / 36;
    const auto sliderHeight = 3 * getHeight() / 5;
    const int paddingTextVertical = getHeight() / 25;
    const int textHeight = 3 * getHeight() / 25;

    const auto paddingTitle = getWidth() / 36;
    const auto modIsActiveButtonWidth = 2*getWidth() / 25;
    const auto paddingHorizontal = getWidth() / 18;

    modIsActiveButton.setBounds(2 * getWidth() / 5-(paddingTitle +modIsActiveButtonWidth)/2, getHeight() / 10, modIsActiveButtonWidth, getHeight() / 10);
    modelEffectTitle.setBounds(modIsActiveButton.getRight()+paddingTitle, getHeight() / 10, getWidth() / 5 + 10, getHeight() / 10);
    
    modWaveTypeBox.setBounds(paddingHorizontal, modelEffectTitle.getBottom()+6*getHeight()/25, 5*getWidth()/18, 4*getHeight()/25);
    modFreqSlider.setBounds(modWaveTypeBox.getRight()+paddingHorizontal, modelEffectTitle.getBottom() + paddingTitle, sliderWidth, sliderHeight);
    modFreqText.setBounds(modWaveTypeBox.getRight() + paddingHorizontal, modFreqSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    modShiftSlider.setBounds(modFreqSlider.getRight() + paddingHorizontal, modelEffectTitle.getBottom() + paddingTitle, sliderWidth, sliderHeight);
    modShiftText.setBounds(modFreqText.getRight() + paddingHorizontal+getWidth()/16, modShiftSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);

}

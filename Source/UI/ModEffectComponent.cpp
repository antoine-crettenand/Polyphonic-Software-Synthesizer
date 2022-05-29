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
    modIsActiveButton.setButtonText("Activate");
    addAndMakeVisible(modIsActiveButton);
    modIsActiveAttachment = std::make_unique<ButtonAttachment>(apvts, nameID + "ModIsActive", modIsActiveButton);

    modFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(modFreqSlider);
    modFreqAttachment = std::make_unique<SliderAttachment>(apvts, nameID + "ModFreq", modFreqSlider);
    
//    modShiftSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    modShiftSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modShiftSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(modShiftSlider);
    modShiftAttachment = std::make_unique<SliderAttachment>(apvts, nameID + "ModShift", modShiftSlider);

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

    const auto bounds = getLocalBounds();

    const double WIDTH_UNUSED_SPACE = bounds.getWidth() / 26;

    modIsActiveButton.setBounds(bounds.getWidth() / 16, 0, bounds.getWidth() / 8, bounds.getHeight()/3);
    
    modFreqSlider.setBounds(bounds.getWidth() / 2 + WIDTH_UNUSED_SPACE, 0, bounds.getWidth() / 4 - 2* WIDTH_UNUSED_SPACE, 2 * bounds.getHeight() / 3);
    
    modWaveTypeBox.setBounds(bounds.getWidth() / 16, bounds.getHeight() / 3, bounds.getWidth() / 2 - 2 * WIDTH_UNUSED_SPACE, bounds.getHeight() / 9);
    
    modShiftSlider.setBounds(2.8*bounds.getWidth() / 4 + WIDTH_UNUSED_SPACE, 0, bounds.getWidth() / 4 - 2 * WIDTH_UNUSED_SPACE, 2 * bounds.getHeight() / 3);
}

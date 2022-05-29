/*
  ==============================================================================

    ModEffectComponent.h
    Created: 26 May 2022 10:24:05am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ModEffectComponent  : public juce::Component
{
public:
    ModEffectComponent(juce::AudioProcessorValueTreeState& apvts, juce::String nameID);
    ~ModEffectComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
//    juce::String nameID;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    juce::ComboBox modWaveTypeBox;
    std::unique_ptr<ComboBoxAttachment> modWaveTypeAttachment;
    
    juce::ToggleButton modIsActiveButton;
    std::unique_ptr<ButtonAttachment> modIsActiveAttachment;

    juce::Slider modFreqSlider;
    std::unique_ptr<SliderAttachment> modFreqAttachment;
    
    juce::Slider modShiftSlider;
    std::unique_ptr<SliderAttachment> modShiftAttachment;
    
    
    void setParameterStyle(juce::Slider& slider);
    juce::String getStringParameter(juce::String pName);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModEffectComponent)
};

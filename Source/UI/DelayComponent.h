/*
  ==============================================================================

    DelayComponent.h
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DelayComponent  : public juce::Component
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState& apvts, juce::String nameID);
    ~DelayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
//    juce::String nameID;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    
    juce::ToggleButton delayIsActiveButton;
    std::unique_ptr<ButtonAttachment> delayIsActiveAttachment;

    juce::Slider timeDelaySlider;
    std::unique_ptr<SliderAttachment> timeDelayAttachment;
    juce::Label timeDelayText;
    
    juce::Slider gainDelaySlider;
    std::unique_ptr<SliderAttachment> gainDelayAttachment;
    juce::Label gainDelayText;
    
    juce::TextButton modelEffectTitle;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};

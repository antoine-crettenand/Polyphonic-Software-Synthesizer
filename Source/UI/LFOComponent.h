/*
  ==============================================================================

    LFOComponent.h
    Created: 18 May 2022 1:55:14am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LFOComponent  : public juce::Component
{
public:
    LFOComponent(juce::AudioProcessorValueTreeState& apvts);
    ~LFOComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider rateSlider;
    juce::Slider mixSlider;
    // target is the module affected by this LFO
    juce::ComboBox targetModuleSelector;
    juce::ComboBox targetComponentSelector;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> targetModuleAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> targetComponentAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};

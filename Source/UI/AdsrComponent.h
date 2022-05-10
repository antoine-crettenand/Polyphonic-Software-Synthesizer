/*
  ==============================================================================

    AdsrComponent.h
    Created: 10 May 2022 12:58:00am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String adsrID);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // used to differentiate between potentially multiple adsr's
    juce::String adsrID;
    
    juce::Slider ampAttackSlider;
    juce::Slider ampDecaySlider;
    juce::Slider ampSustainSlider;
    juce::Slider ampReleaseSlider;
    
    //alias
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> ampAttackAttachment;
    std::unique_ptr<SliderAttachment> ampDecayAttachment;
    std::unique_ptr<SliderAttachment> ampSustainAttachment;
    std::unique_ptr<SliderAttachment> ampReleaseAttachment;
    
    void setParameterStyle(juce::Slider& slider);
    juce::String getStringParameter(juce::String pName);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};

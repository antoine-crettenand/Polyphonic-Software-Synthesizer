/*
  ==============================================================================

    FilterComponent.h
    Created: 14 May 2022 10:58:00am
    Author:  Jonathan Reymond  

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // used to differentiate between potentially multiple filters
    juce::String filterID;
    
    juce::Slider lowCutFreqSlider;
    juce::Label lowCutFreqText;
    juce::Slider highCutFreqSlider;
    juce::Label highCutFreqText;
    juce::Slider peakFreqSlider;
    juce::Label peakFreqText;
    juce::Slider peakGainInDecibelsSlider;
    juce::Label peakGainText;
    juce::Slider peakQualitySlider;
    juce::Label peakQualityText;

    juce::TextButton filterTitle;

    
    //alias
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> lowCutFreqAttachment;
    std::unique_ptr<SliderAttachment> highCutAttachment;
    std::unique_ptr<SliderAttachment> peakFreqAttachment;
    std::unique_ptr<SliderAttachment> peakGainInDecibelsAttachment;
    std::unique_ptr<SliderAttachment> peakQualityAttachment;
    
    void setParameterStyle(juce::Slider& slider);
    juce::String getStringParameter(juce::String pName);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};

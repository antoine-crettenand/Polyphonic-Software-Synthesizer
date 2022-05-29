/*
  ==============================================================================

    DistortionComponent.h
    Created: 28 May 2022 3:12:29am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& apvts);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider preGainSlider;
    juce::Slider postGainSlider;
    juce::Slider highPassFreqSlider;
    
    //alias
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> preGainAttachment;
    std::unique_ptr<SliderAttachment> postGainAttachment;
    std::unique_ptr<SliderAttachment> highPassFreqAttachment;
    
    void setParameterStyle(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};

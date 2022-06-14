/*
  ==============================================================================

    OscComponent.h
    Created: 10 May 2022 2:18:03am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, int oscNumber);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;


    juce::ComboBox oscWaveTypeSelector;
    std::unique_ptr<ComboBoxAttachment> oscWaveTypeSelectorAttachment;
    
    juce::Label oscText;

    juce::Slider freq;
    std::unique_ptr<SliderAttachment> freqAttachment;

    juce::Slider volume;
    std::unique_ptr<SliderAttachment> volumeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};

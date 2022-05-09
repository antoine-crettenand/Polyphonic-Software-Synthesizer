/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class COM418AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    COM418AudioProcessorEditor (COM418AudioProcessor&);
    ~COM418AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider ampAttackSlider;
    juce::Slider ampDecaySlider;
    juce::Slider ampSustainSlider;
    juce::Slider ampReleaseSlider;
    juce::ComboBox oscSelector;
    
    //alias
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> ampAttackAttachment;
    std::unique_ptr<SliderAttachment> ampDecayAttachment;
    std::unique_ptr<SliderAttachment> ampSustainAttachment;
    std::unique_ptr<SliderAttachment> ampReleaseAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    
    //& == reference here to plugin processor
    COM418AudioProcessor& audioProcessor;
    
    void setAmpADSRParametersStyle();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (COM418AudioProcessorEditor)
};

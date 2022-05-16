/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FullOscsComponent.h"

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
    //& == reference here to plugin processor
    COM418AudioProcessor& audioProcessor;
    
    OscComponent osc;
    AdsrComponent ampAdsr;
    FullOscsComponent fullOscsComponent;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    juce::ComboBox oscSelector;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (COM418AudioProcessorEditor)
};

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
#include "UI/FilterComponent.h"
#include "UI/ModEffectComponent.h"
#include "UI/DistortionComponent.h"
#include "UI/WaveformVisualizerComponent.h"

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
    AdsrComponent ampAdsr;
    FullOscsComponent fullOscsComponent;
    FilterComponent filter;
    ModEffectComponent tremolo;
    DistortionComponent distortionComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (COM418AudioProcessorEditor)
};

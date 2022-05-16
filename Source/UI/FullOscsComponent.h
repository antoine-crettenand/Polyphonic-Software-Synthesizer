/*
  ==============================================================================

    FullOscsComponent.h
    Created: 16 May 2022 12:07:33pm
    Author:  Loïc

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FullOscsComponent : public juce::Component
{
public:
    FullOscsComponent(juce::AudioProcessorValueTreeState& apvts);
    ~FullOscsComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    /*juce::BooleanPropertyComponent on1;
    juce::BooleanPropertyComponent on2;
    juce::BooleanPropertyComponent on3;*/

    juce::TextButton frequencyText;
    juce::TextButton waveformText;
    juce::TextButton volumeText;
    
    juce::TextButton oSCText;

    juce::TextButton osc1Text;
    juce::TextButton osc2Text;
    juce::TextButton osc3Text;

    juce::ComboBox oscWaveTypeSelector1;
    juce::ComboBox oscWaveTypeSelector2;
    juce::ComboBox oscWaveTypeSelector3;

    juce::Slider freq1;
    juce::Slider freq2;
    juce::Slider freq3;

    juce::Slider vol1;
    juce::Slider vol2;
    juce::Slider vol3;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FullOscsComponent)
};

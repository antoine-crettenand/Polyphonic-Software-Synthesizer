/*
  ==============================================================================

    FullOscsComponent.h
    Created: 16 May 2022 12:07:33pm
    Author:  Loïc

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
/*
*/
class FullOscsComponent : public juce::Component
{
public:
    FullOscsComponent(juce::AudioProcessorValueTreeState& apvts, int numberOscillators);
    ~FullOscsComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    //void createIndividualOscillators(juce::AudioProcessorValueTreeState& apvts, int numberOscillators);

private:
    std::vector<OscComponent*> oscs;

    juce::Label frequencyText;
    juce::Label waveformText;
    juce::Label volumeText;

    juce::TextButton oSCText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FullOscsComponent)
};

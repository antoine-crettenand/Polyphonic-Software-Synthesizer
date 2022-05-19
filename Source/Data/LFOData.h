/*
  ==============================================================================

    LFOData.h
    Created: 18 May 2022 1:55:31am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class LFOData : public juce::dsp::Oscillator<float>
{
public:
    void updateLFO(const float rate, const float mix, const juce::String moduleName, const juce::String componentName);
    void updateOsc(const float rate);
    juce::String getModuleName() { return moduleName; };
    juce::String getComponentName() { return componentName; };

private:
    float rate;
    float mix;
    juce::String moduleName;
    juce::String componentName;
    
};

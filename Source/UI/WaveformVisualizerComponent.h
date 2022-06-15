/*
  ==============================================================================

    WaveformVisualizerComponent.h
    Created: 4 Jun 2022 4:08:06pm
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformVisualizerComponent  : public juce::AudioVisualiserComponent
{
public:
    WaveformVisualizerComponent(int numChannels, juce::AudioProcessorValueTreeState& apvts);
    
    ~WaveformVisualizerComponent() override;

//    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider gainSlider;
    juce::Label gainLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformVisualizerComponent)
};

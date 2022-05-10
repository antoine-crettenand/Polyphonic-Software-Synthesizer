/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
COM418AudioProcessorEditor::COM418AudioProcessorEditor (COM418AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "Osc1WaveType"), ampAdsr(audioProcessor.apvts, "Amp")
{
    setSize (400, 300);
    
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "Osc1WaveType", oscSelector);
    
    addAndMakeVisible(ampAdsr);
    addAndMakeVisible(osc);
}

COM418AudioProcessorEditor::~COM418AudioProcessorEditor()
{
}

//==============================================================================
void COM418AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void COM418AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    ampAdsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    osc.setBounds(10, 10, 100, 30);
}


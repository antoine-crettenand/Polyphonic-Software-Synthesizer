/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//@TODO : check ampAdsr and filter Id : getStringSetting missing
COM418AudioProcessorEditor::COM418AudioProcessorEditor (COM418AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "Osc1WaveType"), ampAdsr(audioProcessor.apvts, "Amp"), filter(audioProcessor.apvts, "")
{
    setSize (860, 300);
    
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "Osc1WaveType", oscSelector);
    
    addAndMakeVisible(ampAdsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
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
    osc.setBounds(10, 10, 100, 30);

    ampAdsr.setBounds(getWidth() / 4, 0, getWidth() / 4, getHeight());
    filter.setBounds((getWidth() / 4) * 2 + 10, 0, getWidth() / 4, getHeight());
}


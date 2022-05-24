/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
COM418AudioProcessorEditor::COM418AudioProcessorEditor (COM418AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), ampAdsr(audioProcessor.apvts, "Amp"), fullOscsComponent(audioProcessor.apvts, 3) //If we change the number of oscillators in Plugin Processor, we should also change it here
{
    setSize (600, 300);

    addAndMakeVisible(fullOscsComponent);
    addAndMakeVisible(ampAdsr);
}

COM418AudioProcessorEditor::~COM418AudioProcessorEditor()
{
}

//==============================================================================
void COM418AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    juce::Rectangle<int> verticalSeparation(399, 0, 1, 300);

    g.setColour(juce::Colours::lightblue);
    g.fillRect(verticalSeparation);
}

void COM418AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    fullOscsComponent.setBounds(0, 0, 395, 300);
    ampAdsr.setBounds(405, 0, 195, 300);

}


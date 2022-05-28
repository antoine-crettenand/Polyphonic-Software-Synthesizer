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
    : AudioProcessorEditor (&p), audioProcessor (p), ampAdsr(audioProcessor.apvts, "Amp"), filter(audioProcessor.apvts, ""), fullOscsComponent(audioProcessor.apvts, 3), distortionComponent(audioProcessor.apvts) //If we change the number of oscillators in Plugin Processor, we should also change it here
{
    setSize (1655, 600);

    addAndMakeVisible(fullOscsComponent);
    addAndMakeVisible(ampAdsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(distortionComponent);
}

COM418AudioProcessorEditor::~COM418AudioProcessorEditor()
{
}

//==============================================================================
void COM418AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    juce::Rectangle<int> verticalSeparation(400, 0, 1, 300);
    juce::Rectangle<int> verticalSeparation2(630, 0, 1, 300);

    g.setColour(juce::Colours::lightblue);
    g.fillRect(verticalSeparation);
    g.fillRect(verticalSeparation2);

}

void COM418AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    fullOscsComponent.setBounds(0, 0, 395, getHeight());
    ampAdsr.setBounds(405, 0, 220, getHeight());
    filter.setBounds(635, 0, 220, getHeight());
    distortionComponent.setBounds(865, 0, 220, getHeight());
}


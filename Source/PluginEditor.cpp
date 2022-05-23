/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
COM418AudioProcessorEditor::COM418AudioProcessorEditor (COM418AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, 1), osc2(audioProcessor.apvts, 2), osc3(audioProcessor.apvts, 3), ampAdsr(audioProcessor.apvts, "Amp"), fullOscsComponent(audioProcessor.apvts)
{
    setSize (600, 300);

    addAndMakeVisible(ampAdsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);


   addAndMakeVisible(fullOscsComponent);
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
    ampAdsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    //osc.setBounds(10, 10, 100, 30);
    //osc2.setBounds(110, 20, 200, 30);
    //osc3.setBounds(210, 40, 300, 30);
    fullOscsComponent.setBounds(0, 0, 395, 300);
    ampAdsr.setBounds(405, 0, 195, 300);

}


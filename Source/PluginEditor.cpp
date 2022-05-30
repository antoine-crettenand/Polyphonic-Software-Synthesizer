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
    : AudioProcessorEditor (&p), audioProcessor (p), ampAdsr(audioProcessor.apvts, "Amp"),
    fullOscsComponent(audioProcessor.apvts, 3), //If we change the number of oscillators in Plugin Processor, we should also change it here
    filter(audioProcessor.apvts, ""),
    tremolo(audioProcessor.apvts, "tremolo"),
    distortionComponent(audioProcessor.apvts)

{

    setSize (1600, 600);

    addAndMakeVisible(fullOscsComponent);
    addAndMakeVisible(ampAdsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(tremolo);
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

    auto componentWidth = getWidth() / 5;
    juce::Rectangle<int> verticalSeparation(componentWidth * 1, 0, 1, getHeight());
    juce::Rectangle<int> verticalSeparation2(componentWidth * 2, 0, 1, getHeight());
    juce::Rectangle<int> verticalSeparation3(componentWidth * 3, 0, 1, getHeight());
    juce::Rectangle<int> verticalSeparation4(componentWidth * 4, 0, 1, getHeight());

    g.setColour(juce::Colours::lightblue);
    g.fillRect(verticalSeparation);
    g.fillRect(verticalSeparation2);
    g.fillRect(verticalSeparation3);
    g.fillRect(verticalSeparation4);

}

void COM418AudioProcessorEditor::resized()
{
    auto componentWidth = getWidth() / 6;
    auto componentHeight = getHeight();
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    fullOscsComponent.setBounds(0, 0, 2 * componentWidth, componentHeight);
    ampAdsr.setBounds(fullOscsComponent.getRight(), 0, componentWidth, componentHeight);
    filter.setBounds(ampAdsr.getRight(), 0, componentWidth, componentHeight);
    tremolo.setBounds(filter.getRight(), 0, componentWidth, componentHeight);
    distortionComponent.setBounds(tremolo.getRight(), 0, componentWidth, componentHeight);
}


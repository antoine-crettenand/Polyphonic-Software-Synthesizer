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

    setSize (1000, 600);

    addAndMakeVisible(fullOscsComponent);
    addAndMakeVisible(ampAdsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(tremolo);
    addAndMakeVisible(distortionComponent);
    
    addAndMakeVisible(audioProcessor.waveformVisualizer);
}

COM418AudioProcessorEditor::~COM418AudioProcessorEditor()
{
}

//==============================================================================
void COM418AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    
    auto smallComponentWidth = (3 * getWidth() / 10);
    auto smallComponentHeight = getHeight() / 2;
    juce::Rectangle<int> verticalSeparation(4 * smallComponentWidth / 3 -1, 0, 2, getHeight());
    juce::Rectangle<int> verticalSeparation2(7 * smallComponentWidth / 3 - 1, 0, 2, getHeight());
    juce::Rectangle<int> horizontalSeparation1(4 * smallComponentWidth / 3 - 1, smallComponentHeight-1, getWidth()-(4 * smallComponentWidth / 3 - 1), 2);
    juce::Rectangle<int> horizontalSeparation2(7 * smallComponentWidth / 3 - 1, smallComponentHeight-1, getWidth()-(4 * smallComponentWidth / 3 - 1), 2);

    g.setColour(juce::Colours::lightblue);
    g.fillRect(verticalSeparation);
    g.fillRect(verticalSeparation2);
    g.fillRect(horizontalSeparation1);
    g.fillRect(horizontalSeparation2);
    
    audioProcessor.waveformVisualizer.setColours(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));
}

void COM418AudioProcessorEditor::resized()
{
    auto smallComponentWidth = (3*getWidth() / 10);
    auto smallComponentHeight = getHeight()/2;
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    fullOscsComponent.setBounds(0, 0, 4* smallComponentWidth/3-1, getHeight());
    ampAdsr.setBounds(fullOscsComponent.getRight()+2, 0, smallComponentWidth-2, smallComponentHeight-1);
    filter.setBounds(fullOscsComponent.getRight()+2, ampAdsr.getBottom()+2, smallComponentWidth-2, smallComponentHeight-1);
    tremolo.setBounds(ampAdsr.getRight()+2, 0, smallComponentWidth-1, smallComponentHeight-1);
    distortionComponent.setBounds(filter.getRight()+2, tremolo.getBottom()+2, smallComponentWidth-1, smallComponentHeight-1);
    audioProcessor.waveformVisualizer.setBounds(distortionComponent.getRight(), componentHeight * .5f, componentWidth, componentHeight * .5f);
}


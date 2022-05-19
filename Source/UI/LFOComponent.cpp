/*
  ==============================================================================

    LFOComponent.cpp
    Created: 18 May 2022 1:55:14am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComponent.h"

//==============================================================================
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    
    juce::StringArray moduleChoices = {"OSC", "FILTER", "AMP"};
    targetModuleSelector.addItemList(moduleChoices, 1);
    
    juce::StringArray componentChoices = {"ADSRAttack", "ADSRDecay", "ADSRSustain", "ADSRRelease", "Freq", "Gain"};
    targetComponentSelector.addItemList(componentChoices, 1);
    
    targetModuleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "LFOTargetModule", targetModuleSelector);
    targetComponentAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "LFOTargetComponent", targetComponentSelector);
    rateAttachment = std::make_unique<SliderAttachment>(apvts, "LFORate", rateSlider);
    mixAttachment = std::make_unique<SliderAttachment>(apvts, "LFOMix", mixSlider);
    
    // @TODO need to make it visible
}

LFOComponent::~LFOComponent()
{
}

void LFOComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("LFOComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void LFOComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
COM418AudioProcessorEditor::COM418AudioProcessorEditor (COM418AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (400, 300);
    //allocate memory
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    ampAttackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "AmpAttack", ampAttackSlider);
    ampDecayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "AmpDecay", ampDecaySlider);
    ampSustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "AmpSustain", ampSustainSlider);
    ampReleaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "AmpRelease", ampReleaseSlider);
    
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);
        
    setAmpADSRParametersStyle();
}

COM418AudioProcessorEditor::~COM418AudioProcessorEditor()
{
}

//==============================================================================
void COM418AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void COM418AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() / 4 - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);
    
    ampAttackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    ampDecaySlider.setBounds(ampAttackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    ampSustainSlider.setBounds(ampDecaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    ampReleaseSlider.setBounds(ampSustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void COM418AudioProcessorEditor::setAmpADSRParametersStyle(){
    // Set sliders to vertical
    ampAttackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ampDecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ampSustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ampReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    
    //
    ampAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    ampDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    ampSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    ampReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
}

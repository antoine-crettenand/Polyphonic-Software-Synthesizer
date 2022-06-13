/*
  ==============================================================================

    FilterComponent.cpp
    Created: 14 May 2022 10:58:00am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterID) : filterID(filterID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    lowCutFreqAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("LowCutFreq"), lowCutFreqSlider);
    highCutAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("HighCutFreq"), highCutFreqSlider);
    peakFreqAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("PeakFreq"), peakFreqSlider);
    peakGainInDecibelsAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("PeakGain"), peakGainInDecibelsSlider);
    peakQualityAttachment = std::make_unique<SliderAttachment>(apvts, getStringParameter("PeakQuality"), peakQualitySlider);


    setParameterStyle(lowCutFreqSlider);
    setParameterStyle(highCutFreqSlider);
    setParameterStyle(peakFreqSlider);
    setParameterStyle(peakGainInDecibelsSlider);
    setParameterStyle(peakQualitySlider);


    lowCutFreqText.setText("Low cut", juce::dontSendNotification);
    highCutFreqText.setText("High cut", juce::dontSendNotification);
    peakFreqText.setText("Peak freq", juce::dontSendNotification);
    peakGainText.setText("Peak gain", juce::dontSendNotification);
    peakQualityText.setText("Peak quality", juce::dontSendNotification);

    filterTitle.setButtonText("Filters");
    filterTitle.setColour(juce::TextButton::textColourOffId, juce::Colours::lightblue);

    addAndMakeVisible(lowCutFreqText);
    addAndMakeVisible(highCutFreqText);
    addAndMakeVisible(peakFreqText);
    addAndMakeVisible(peakGainText);
    addAndMakeVisible(peakQualityText);
    addAndMakeVisible(filterTitle);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void FilterComponent::resized()
{
    
    const auto sliderWidth = getWidth() / 6;
    const auto sliderHeight = 3 * getHeight() / 5;
    const int padding = getWidth()/36;
    const int paddingTextVertical = getHeight() / 25;
    const int textHeight = 3*getHeight() / 25;
    
    filterTitle.setBounds(2*getWidth() / 5, getHeight() / 10, getWidth() / 5, getHeight() / 10);

    lowCutFreqSlider.setBounds(padding, filterTitle.getBottom() + padding, sliderWidth, sliderHeight);
    lowCutFreqText.setBounds(padding, lowCutFreqSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    highCutFreqSlider.setBounds(lowCutFreqSlider.getRight() + padding, filterTitle.getBottom() + padding, sliderWidth, sliderHeight);
    highCutFreqText.setBounds(lowCutFreqSlider.getRight() + padding, highCutFreqSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    peakFreqSlider.setBounds(highCutFreqSlider.getRight() + padding, filterTitle.getBottom() + padding, sliderWidth, sliderHeight);
    peakFreqText.setBounds(highCutFreqSlider.getRight() + padding, peakFreqSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    peakGainInDecibelsSlider.setBounds(peakFreqSlider.getRight() + padding, filterTitle.getBottom() + padding, sliderWidth, sliderHeight);
    peakGainText.setBounds(peakFreqSlider.getRight() + padding, peakGainInDecibelsSlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);
    peakQualitySlider.setBounds(peakGainInDecibelsSlider.getRight() + padding, filterTitle.getBottom() + padding, sliderWidth, sliderHeight);
    peakQualityText.setBounds(peakGainInDecibelsSlider.getRight() + padding, peakQualitySlider.getBottom() + paddingTextVertical, sliderWidth, textHeight);


}

void FilterComponent::setParameterStyle(juce::Slider& slider){
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

// @TODO find a cleaner way of retrieving attachment keywords from apvts
juce::String FilterComponent::getStringParameter(juce::String pName){
    return filterID + pName;
}

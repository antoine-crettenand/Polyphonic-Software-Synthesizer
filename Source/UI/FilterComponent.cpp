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
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;
    
    lowCutFreqSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    highCutFreqSlider.setBounds(lowCutFreqSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    peakFreqSlider.setBounds(highCutFreqSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    peakGainInDecibelsSlider.setBounds(peakFreqSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    peakQualitySlider.setBounds(peakGainInDecibelsSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
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

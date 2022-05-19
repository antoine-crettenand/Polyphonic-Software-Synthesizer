/*
  ==============================================================================

    LFOData.cpp
    Created: 18 May 2022 1:55:31am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include "LFOData.h"

void LFOData::updateLFO(const float rate, const float mix, const juce::String moduleName, const juce::String componentName){
    this->rate = rate;
    this->mix = mix;
    this->moduleName = moduleName;
    this->componentName = componentName;
}

void LFOData::updateOsc(const float rate)
{
  initialise([=](float x){ return std::sin(2 * juce::MathConstants<float>::pi * rate * x); });
}

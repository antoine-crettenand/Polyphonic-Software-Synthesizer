/*
  ==============================================================================

    OscData.h
    Created: 10 May 2022 1:59:36am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void setWaveType(const int choice);
    juce::StringArray getWaveTypeChoices(){return {"Sine", "Saw", "Square"};}
    
private:
    
    
};

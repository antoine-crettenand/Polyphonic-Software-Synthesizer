/*
  ==============================================================================

    Synth.h
    Created: 25 May 2022 1:53:54pm
    Author:  Loïc

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

class Synth : public juce::Synthesiser
{
public:
    void noteOn(const int midiChannel, const int midiNoteNumber, const float velocity) override;

private:

};
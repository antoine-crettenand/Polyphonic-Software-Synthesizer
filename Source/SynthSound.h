/*
  ==============================================================================

    SynthSound.h
    Created: 2 May 2022 10:02:13am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }
    
};

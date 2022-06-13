/*
  ==============================================================================

    Synth.h
    Created: 25 May 2022 1:53:54pm
    Author:  Loïc

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"


class Synth : public juce::Synthesiser
{
public:
    void noteOn(const int midiChannel, const int midiNoteNumber, const float velocity) override;
    juce::SynthesiserVoice* findVoiceToSteal(juce::SynthesiserSound* soundToPlay,
        int /*midiChannel*/, int midiNoteNumber) const override;
    void setNumberPolyphony(int polyphony) {numberPolyphony = polyphony;};
    int getNumberPolyphony() {return numberPolyphony;};
    void setNumberOscillators(int oscillators) { numberOscillators = oscillators; };
    int getNumberOscillators() { return numberOscillators; };

private:
    // Default values, if you want to change them, check constructor of PluginProcessor.cpp where the setNumberPolyphony and setNumberOscillators methods are called
    int numberPolyphony = 7;
    int numberOscillators = 3;
};
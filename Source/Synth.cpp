/*
  ==============================================================================

    Synth.cpp
    Created: 25 May 2022 1:53:54pm
    Author:  Loïc

  ==============================================================================
*/
#include <JuceHeader.h>
#include "Synth.h"

void Synth::noteOn(const int midiChannel, const int midiNoteNumber, const float velocity) {
    
    const juce::CriticalSection::ScopedLockType sl(lock);

    for (auto* sound : sounds)
    {
        if (sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
        {
            for (auto* voice : voices) {
                // By default, isNoteStealingEnabled is set to true => We just start all our voices with the new midiNote (this method make sure to stop the note that was playing before).
                if (isNoteStealingEnabled()) {
                    startVoice(voice, sound, midiChannel, midiNoteNumber, velocity);
                }
                // Otherwise default behavior. Will either let the previous note finish and ignore this midiNote if the voices were playing or will play the new midiNote otherwise.
                else {
                    if (voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel(midiChannel)) {
                        stopVoice(voice, 1.0f, true);
                    }
                    startVoice(findFreeVoice(sound, midiChannel, midiNoteNumber, isNoteStealingEnabled()),
                        sound, midiChannel, midiNoteNumber, velocity);
                }

            }


        }
    }
}

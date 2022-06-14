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
            // If hitting a note that's still ringing, stop it first (it could be
            // still playing because of the sustain or sostenuto pedal).
            for (auto* voice : voices)
                if (voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel(midiChannel))
                    stopVoice(voice, 1.0f, true);

            for (int i = 0; i < numberOscillators; ++i) {
                startVoice(findFreeVoice(sound, midiChannel, midiNoteNumber, isNoteStealingEnabled()),
                    sound, midiChannel, midiNoteNumber, velocity);
            }
        }
    }
}

juce::SynthesiserVoice* Synth::findVoiceToSteal(juce::SynthesiserSound* soundToPlay,
    int /*midiChannel*/, int midiNoteNumber) const
{
    // This voice-stealing algorithm applies the following heuristic:
    // - Re-use the oldest notes

    // apparently you are trying to render audio without having any voices...
    jassert(!voices.isEmpty());

    // this is a list of voices we can steal, sorted by how long they've been running
    juce::Array<juce::SynthesiserVoice*> usableVoices;
    usableVoices.ensureStorageAllocated(voices.size());

    for (auto* voice : voices)
    {
        if (voice->canPlaySound(soundToPlay))
        {
            jassert(voice->isVoiceActive()); // We wouldn't be here otherwise

            usableVoices.add(voice);

            // NB: Using a functor rather than a lambda here due to scare-stories about
            // compilers generating code containing heap allocations..
            struct Sorter
            {
                bool operator() (const juce::SynthesiserVoice* a, const juce::SynthesiserVoice* b) const noexcept { return a->wasStartedBefore(*b); }
            };

            std::sort(usableVoices.begin(), usableVoices.end(), Sorter());
        }
    }

    // Oldest voice
    return usableVoices[0];

}

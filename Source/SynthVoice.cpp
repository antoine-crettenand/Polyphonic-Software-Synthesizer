/*
  ==============================================================================

    SynthVoice.cpp
    Created: 2 May 2022 10:00:55am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "SynthVoice.h"
//will return true if have a sound loaded
bool SynthVoice::canPlaySound (juce::SynthesiserSound *sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    if(!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }
}
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    //ADSR
    adsr.setSampleRate(sampleRate);
    //oscillator init
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    //pass to component the spec (pass reference)
    osc.prepare(spec);
    gain.prepare(spec);
    
//    osc.setFrequency(220.0f);
    //linear : between 0 and 1
    gain.setGainLinear(0.06f);
    
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.8f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.5f; //sec
    
    adsr.setParameters(adsrParams);
    
    isPrepared = true;
}
void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    //if nothing, do nothing
    if(!isVoiceActive())
    {
        return;
    }
    //see doc
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    // type we process, only points to buffer, is an alias, (here construct one object)//same
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer};
    //process and store result wrt context, read buffer and write into it
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    //audioblock already processed by osc (wait until osc process done with block)
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    //adsr, not audioBlock since expect another type (but same)
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    for(int channel = 0; channel < outputBuffer.getNumChannels(); ++ channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        //if adsr not active => rendernextblock doc
        if(!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
    
}

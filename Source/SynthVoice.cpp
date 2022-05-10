/*
  ==============================================================================

    SynthVoice.cpp
    Created: 2 May 2022 10:00:55am
    Author:  Jonathan Reymond

  ==============================================================================
*/

#include "SynthVoice.h"
#include "Data/AdsrData.h"
//will return true if have a sound loaded
bool SynthVoice::canPlaySound (juce::SynthesiserSound *sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    ampAdsr.noteOn();
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    ampAdsr.noteOff();
    if(!allowTailOff || !ampAdsr.isActive())
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
    ampAdsr.setSampleRate(sampleRate);
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
    
    isPrepared = true;
}

float ms2sec(const float sec){
    return sec * 0.001;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release){
    ampAdsr.updateADSR(attack, decay, sustain, release);
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
    ampAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    for(int channel = 0; channel < outputBuffer.getNumChannels(); ++ channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        //if adsr not active => rendernextblock doc
        if(!ampAdsr.isActive())
        {
            clearCurrentNote();
        }
    }
    
}

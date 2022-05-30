/*
  ==============================================================================

    OscData.cpp
    Created: 10 May 2022 1:59:36am
    Author:  Antoine Crettenand

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int choice)
{
    /*
     sin wave : return std::sin(x)
     square wave : return x < 0.0f ? -1.0f : 1.0f;
     saw wave : return x / juce::MathConstants<float>::pi; (scie /|/|)
     => more efficient when change freq : use lookup table
     */

    
    switch (choice) {
        case 0:
            //Sine wave
            initialise([this](float x){ return std::sin(x + this->shift); });
            break;
            
        case 1:
            //Saw wave
            initialise([this](float x){
                float xShifted = x + this->shift;
                if(xShifted > juce::MathConstants<float>::pi){
                    xShifted -= juce::MathConstants<float>::twoPi;
                }
                return (xShifted) / juce::MathConstants<float>::pi;
                
            });
            break;
            
        case 2:
            //Square wave :
            initialise([this](float x){
                float xShifted = x + this->shift;
                if(xShifted > juce::MathConstants<float>::pi){
                    xShifted -= juce::MathConstants<float>::twoPi;
                }
                return xShifted < 0.0f ? -1.0f : 1.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setFrequencyNote(int midiNoteNumber) {
    int newNoteNumber = midiNoteNumber + semiTonesUp;
    //Clamp between 0 and 127 which are the lowest and highest values in midi format
    newNoteNumber = newNoteNumber > 127 ? 127 : newNoteNumber;
    newNoteNumber = newNoteNumber < 0 ? 0 : newNoteNumber;

    juce::dsp::Oscillator<float>::setFrequency(juce::MidiMessage::getMidiNoteInHertz(newNoteNumber));
}



void OscData::setSemiTonesUp(int semiTones) {
    semiTonesUp = semiTones;
}



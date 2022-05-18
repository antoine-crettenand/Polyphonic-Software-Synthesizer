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
            initialise([](float x){ return std::sin(x); });
            break;
            
        case 1:
            //Saw wave
            initialise([](float x){ return x / juce::MathConstants<float>::pi; });
            break;
            
        case 2:
            //Square wave
            initialise([](float x){ return x < 0.0f ? -1.0f : 1.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}
/*
  ==============================================================================

    TremoloData.h
    Created: 21 May 2022 6:23:29pm
    Author:  Jonathan Reymond

  ==============================================================================
*/

#pragma once
#include "ModEffectData.h"


class TremoloData : public ModEffectData
{
public :
    TremoloData(): ModEffectData("tremolo")
    {
    }
    void processBlock(juce::AudioBuffer<float>& buffer) override;

private :
};

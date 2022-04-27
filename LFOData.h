/*
  ==============================================================================

    LFOData.h
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VirtualOsc.h"

class LFOData : public VirtualOsc {
public:
    float processBlock(juce::dsp::AudioBlock<float>& block);
    void setFreq(const float rate);
    void setParams(float lfoRate, float lfoInt, int lfoWaveType);
    float mod{ 0.0f };

private:
    float intensity{ 0.0f };
};

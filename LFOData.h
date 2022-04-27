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
    /// <summary>
    /// Processes input values into floats suitable for audio output.
    /// </summary>
    /// <param name="block">Block of sample data</param>
    /// <returns>Audio data</returns>
    float processBlock(juce::dsp::AudioBlock<float>& block);

    /// <summary>
    /// Sets frequency.
    /// </summary>
    void setFreq(const float rate);

    /// <summary>
    /// Sets parameters.
    /// </summary>
    void setParams(float lfoRate, float lfoInt, int lfoWaveType);

    float mod{ 0.0f };

private:
    float intensity{ 0.0f };
};

/*
  ==============================================================================

    LFOData.cpp
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOData.h"

float LFOData::processBlock(juce::dsp::AudioBlock<float>& block) {
    return processSample(block.getSample(0, 0))*intensity;
}

void LFOData::setFreq(const float rate) {
    setFrequency(rate);
}

void LFOData::setParams(float lfoRate, float lfoInt, int lfoWaveType) {
    setWaveType(lfoWaveType);
    setFreq(lfoRate);
    intensity = lfoInt;
}

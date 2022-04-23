/*
  ==============================================================================

    LFOData.cpp
    Created: 26 Mar 2022 1:26:37pm
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOData.h"

void LFOData::setWaveType(const int waveType) {

    switch (waveType)
    {
    case 0:
        initialise([](float x) {return std::sin(x); });
        break;
    case 1:
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;
    case 2:
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
        break;
    default:
        jassertfalse; //error
        break;
    }
}

void LFOData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
    prepare(spec);
}

void LFOData::processBlock(juce::dsp::AudioBlock<float>& block) {
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void LFOData::setFreq(const float rate) {
    setFrequency(rate);
}

void LFOData::setParams(float lfoRate, float lfoInt, int lfoWaveType) {
    setWaveType(lfoWaveType);
    setFreq(lfoRate);
    //setInt(lfoInt);
}

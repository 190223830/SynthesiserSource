/*
  ==============================================================================

    LFOData.cpp
    Created: 26 Mar 2022 1:26:37pm
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOData.h"

<<<<<<< Updated upstream
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
=======
float LFOData::processBlock(juce::dsp::AudioBlock<float>& block) {
    return processSample(block.getSample(0, 0)) * intensity;
    for (int channel = 0; channel < block.getNumChannels(); channel++) {
        for (int sample = 0; sample < block.getNumSamples(); sample++) {
            return processSample(block.getSample(channel, sample))*intensity;
        }
    }
>>>>>>> Stashed changes
}

void LFOData::processBlock(juce::dsp::AudioBlock<float>& block) {
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void LFOData::setFreq(const float rate) {
    setFrequency(rate);
}

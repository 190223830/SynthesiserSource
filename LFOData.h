/*
  ==============================================================================

    LFOData.h
    Created: 26 Mar 2022 1:26:37pm
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscData.h"

class LFOData : public juce::dsp::Oscillator<float> { //this may need to inherit from oscdata once more modulation parameters are in place
public:
    void LFOData::setWaveType(const int waveType);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void processBlock(juce::dsp::AudioBlock<float>& block);
    void LFOData::setFreq(const float rate);


private:

};

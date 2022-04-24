/*
  ==============================================================================

    LFOData.h
    Created: 26 Mar 2022 1:26:37pm
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "OscData.h"

class LFOData : public juce::dsp::Oscillator<float> { //this may need to inherit from oscdata once more modulation parameters are in place
public:
    LFOData();
    void LFOData::setWaveType(const int waveType);
    void processBlock(juce::dsp::AudioBlock<float>& block);
    void LFOData::setFreq(const float rate);
    void setParams(float lfoRate, float lfoInt, int lfoWaveType);
    float mod{ 0.0f };

private:
    float intensity{ 0.0f };
    
    
};

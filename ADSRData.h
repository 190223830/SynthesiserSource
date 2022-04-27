/*
  ==============================================================================

    ADSRData.h
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRData : public juce::ADSR {
public:
    void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;

};

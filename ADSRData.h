/*
  ==============================================================================

    ADSRData.h
    Created: 2 Feb 2022 10:17:58am
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRData : public juce::ADSR {
public:
    void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    //juce::ADSR::ADSR;
    juce::ADSR::Parameters adsrParams;

};

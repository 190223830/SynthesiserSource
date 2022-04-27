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
    /// <summary>
    /// Sets the parameters for attack, decay, sustain and release for a given component.
    /// </summary>
    /// <param name="attack"> attack value </param>
    /// <param name="decay"> decay value </param>
    /// <param name="sustain"> sustain value </param>
    /// <param name="release"> release </param>
    void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;

};

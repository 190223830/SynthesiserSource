/*
  ==============================================================================

    ADSR.h
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils.h"

class ADSR  : public juce::Component
{
public:
    ADSR(juce::AudioProcessorValueTreeState& valueTreeState,
        juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID, 
        juce::String modulationTarget = "");
    ~ADSR() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    GenericSlider attackSlider, decaySlider, sustainSlider, releaseSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSR)
};

/*
  ==============================================================================

    Osc.h
    Created: 2 Feb 2022 3:49:21pm
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Osc  : public juce::Component
{
public:
    Osc(juce::AudioProcessorValueTreeState& valueTreeState, juce::String wave);
    ~Osc() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox waveSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc)
};

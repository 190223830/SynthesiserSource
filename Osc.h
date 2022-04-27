/*
  ==============================================================================

    Osc.h
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils.h"

class Osc  : public juce::Component
{
public:
    Osc(juce::AudioProcessorValueTreeState& valueTreeState, juce::String wave, juce::String modOneFreqID, juce::String modOneIntID, juce::String modOneWaveID);
    ~Osc() override;

    /// <summary>
    /// Re-skins the component.
    /// </summary>
    void paint (juce::Graphics&) override;

    /// <summary>
    /// How the component will be laid out on screen.
    /// </summary>
    void resized() override;

private:
    juce::ComboBox waveSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;
    juce::Label waveSelectLabel{ "waveSelectLabel", "Oscillator Wave Type" };

    juce::ComboBox modOneWaveSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> modOneWaveSelectAttachment;
    juce::Label modOneWaveSelectLabel{ "modOneWaveSelectLabel", "Modulator Wave Type" };
  

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Osc)
};

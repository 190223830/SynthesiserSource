/*
  ==============================================================================

    Filter.h
    Created: 12 Feb 2022 3:00:26pm
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Filter  : public juce::Component
{
public:
    Filter(juce::AudioProcessorValueTreeState& valueTreeState, juce::String type);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterType;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;

    juce::Slider filterCutoff;
    juce::Slider filterResonance;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
    juce::Label filterCutoffLabel{ "filterCutoffLabel", "Cutoff Frequency" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;
    juce::Label filterResonanceLabel{ "filterResonanceLabel", "Resonance" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

/*
  ==============================================================================

    Filter.h
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils.h"

class Filter  : public juce::Component
{
public:
    Filter(juce::AudioProcessorValueTreeState& valueTreeState, juce::String type);
    ~Filter() override;

    /// <summary>
    /// Re-skins the component.
    /// </summary>
    void paint (juce::Graphics&) override;

    /// <summary>
    /// How the component will be laid out on screen.
    /// </summary>
    void resized() override;

private:
    juce::ComboBox filterType;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;

    GenericSlider filterCutoffSlider;
    GenericSlider filterResonanceSlider;
    GenericSlider modIntensitySlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

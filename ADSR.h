/*
  ==============================================================================

    ADSR.h
    Created: 2 Feb 2022 10:16:55am
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    juce::Label attackLabel{ "attackLabel", "Attack" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    juce::Label decayLabel{ "decayLabel", "Decay" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    juce::Label sustainLabel{ "sustainLabel", "Sustain" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    juce::Label releaseLabel{ "releaseLabel", "Release" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSR)
};

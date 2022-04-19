/*
  ==============================================================================

    LFO.h
    Created: 26 Mar 2022 11:59:36am
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils.h"
#include "Osc.h"

class LFO : public Utils
{
public:
    LFO(juce::AudioProcessorValueTreeState& apvts, juce::String lfoRateId, juce::String lfoIntId, juce::String lfoWaveId);
    ~LFO() override;
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::ComboBox lfoWaveSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> lfoWaveSelectAttachment;

    //void setSliderParams(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::String parameter, juce::AudioProcessorValueTreeState& valueTreeState);
    GenericSlider lfoRate, lfoInt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO)
};

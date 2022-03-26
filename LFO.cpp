/*
  ==============================================================================

    LFO.cpp
    Created: 26 Mar 2022 11:59:36am
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFO.h"

LFO::LFO(juce::AudioProcessorValueTreeState& valueTreeState, juce::String lfoRateId, juce::String lfoIntId, juce::String lfoWaveId)
    : lfoRate("Rate", lfoRateId, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
    , lfoInt("Intensity", lfoIntId, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    juce::StringArray waves{ "Sine", "Saw", "Square" };
    lfoWaveSelect.addItemList(waves, 1);
    addAndMakeVisible(lfoWaveSelect);
    lfoWaveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, lfoWaveId, lfoWaveSelect);

    addAndMakeVisible(lfoRate);
    addAndMakeVisible(lfoInt);
    addAndMakeVisible(lfoWaveSelect);
}

LFO::~LFO()
{
}

void LFO::resized()
{
    lfoWaveSelect.setBounds(0, 0, 100, 50);
    lfoRate.setBounds(getWidth()/2, 0, 100, getHeight());
    lfoInt.setBounds(getWidth() /2 + 100, 0, 100, getHeight());
}

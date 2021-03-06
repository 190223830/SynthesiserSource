/*
  ==============================================================================

    LFO.cpp
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

void LFO::paint(juce::Graphics& g){}

void LFO::resized()
{
    lfoWaveSelect.setBounds(0, 35, 70, 40);
    lfoRate.setBounds(lfoWaveSelect.getRight(), 0, 70, 75);
    lfoInt.setBounds(lfoRate.getRight(), 0, 70, 75);
}

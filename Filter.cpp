/*
  ==============================================================================

    Filter.cpp
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"


Filter::Filter(juce::AudioProcessorValueTreeState& valueTreeState, juce::String type)

    : filterCutoffSlider("Cutoff", "CUTOFF", valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    filterResonanceSlider("Resonance", "RESONANCE", valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    modIntensitySlider("Intensity", "EGINT", valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    juce::StringArray types{ "LPF", "BPF", "HPF" };
    filterType.addItemList(types, 1);
    addAndMakeVisible(filterType);
    waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, type, filterType);

    addAndMakeVisible(filterCutoffSlider);
    addAndMakeVisible(filterResonanceSlider);
    addAndMakeVisible(modIntensitySlider);

}

Filter::~Filter(){}
void Filter::paint (juce::Graphics& g) {}

void Filter::resized()
{
    filterType.setBounds(0, 35, 70, 40);
    filterCutoffSlider.setBounds(filterType.getRight(), 0, 70, 75);
    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), 0, 70, 75);
    modIntensitySlider.setBounds(0, 70, 70, 75);
}


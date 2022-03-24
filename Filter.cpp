/*
  ==============================================================================

    Filter.cpp
    Created: 12 Feb 2022 3:00:26pm
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

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    //g.setColour(juce::Colours::white);
    //g.drawRect(getLocalBounds());
}

void Filter::resized()
{
    filterType.setBounds(getWidth()/3, 35, getWidth()/6, 40);
    filterCutoffSlider.setBounds(getWidth()/2, 0, getWidth()/4, getHeight()/2);
    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), 0, getWidth()/4, getHeight() / 2);
    modIntensitySlider.setBounds(0, getHeight()/2, getWidth()/5, getHeight()/2);
}

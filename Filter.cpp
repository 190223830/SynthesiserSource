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
{
    juce::StringArray types{ "LPF", "BPF", "HPF" };
    filterType.addItemList(types, 1);
    addAndMakeVisible(filterType);
    waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, type, filterType);

    filterCutoff.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    filterCutoff.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 150, 20);
    filterResonance.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResonance.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);

    addAndMakeVisible(filterCutoff);
    filterCutoffLabel.setFont(15.0f);
    filterCutoffLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterCutoffLabel);

    addAndMakeVisible(filterResonance);
    filterResonanceLabel.setFont(15.0f);
    filterResonanceLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterResonanceLabel);

    filterCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "CUTOFF", filterCutoff);
    filterResonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "RESONANCE", filterResonance);
}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    //g.setColour(juce::Colours::white);
    //g.drawRect(getLocalBounds());
}

void Filter::resized()
{
    filterType.setBounds(0, (getHeight()/2)+50, 100, 40);

    filterCutoff.setBounds(70, 0, getWidth()-70, 100); //TODO: create a new class/component that has a constructor that does all of this
    filterCutoffLabel.setBounds(filterCutoff.getX(), 100, filterCutoff.getWidth(), 20);

    filterResonance.setBounds(0, 0, 70, 100);
    filterResonanceLabel.setBounds(filterResonance.getX(), filterResonance.getY() + filterResonance.getHeight(), filterResonance.getWidth(), 20);
}

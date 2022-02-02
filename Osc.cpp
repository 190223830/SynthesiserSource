/*
  ==============================================================================

    Osc.cpp
    Created: 2 Feb 2022 3:49:21pm
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Osc.h"

Osc::Osc(juce::AudioProcessorValueTreeState& valueTreeState, juce::String wave)
{
    juce::StringArray waves{ "Sine", "Saw", "Square"};
    waveSelect.addItemList(waves, 1);
    addAndMakeVisible(waveSelect);
    waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, wave, waveSelect);
}

Osc::~Osc()
{
}

void Osc::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void Osc::resized()
{
    waveSelect.setBounds(getLocalBounds());
}

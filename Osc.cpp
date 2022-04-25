/*
  ==============================================================================

    Osc.cpp
    Created: 2 Feb 2022 3:49:21pm
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Osc.h"

Osc::Osc(juce::AudioProcessorValueTreeState& valueTreeState, juce::String wave, juce::String modOneFreqID, juce::String modOneIntID, juce::String modOneWaveID)
{
    juce::StringArray waves{ "Sine", "Saw", "Square"};
    waveSelect.addItemList(waves, 1);
    addAndMakeVisible(waveSelect);
    waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, wave, waveSelect);

    waveSelectLabel.setFont(15.0f);
    waveSelectLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(waveSelectLabel);

}

Osc::~Osc()
{
}

void Osc::paint (juce::Graphics& g)
{
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    /*g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());*/

}

void Osc::resized()
{
    waveSelect.setBounds(0, 20, 70, 40);
    waveSelectLabel.setBounds(0, 70, 150, 20);

}

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
    : modOneFreqSlider("Frequency", modOneFreqID, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    modOneIntSlider("Intensity", modOneIntID, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    juce::StringArray waves{ "Sine", "Saw", "Square"};
    waveSelect.addItemList(waves, 1);
    addAndMakeVisible(waveSelect);
    waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, wave, waveSelect);

    waveSelectLabel.setFont(15.0f);
    waveSelectLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(waveSelectLabel);
    modOneWaveSelect.addItemList(waves, 1);
    addAndMakeVisible(modOneWaveSelect);
    modOneWaveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, modOneWaveID, modOneWaveSelect);

    modOneWaveSelectLabel.setFont(15.0f);
    modOneWaveSelectLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modOneWaveSelectLabel);

    addAndMakeVisible(modOneFreqSlider);
    addAndMakeVisible(modOneIntSlider);
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
    waveSelect.setBounds(15, 20, 100, 40);
    waveSelectLabel.setBounds(waveSelect.getX() + waveSelect.getWidth() + 10, waveSelect.getY() + waveSelect.getHeight() / 4, 150, 20);
    
    modOneWaveSelect.setBounds(15, getHeight() / 2, 100, 40);
    modOneWaveSelectLabel.setBounds(modOneWaveSelect.getX() + modOneWaveSelect.getWidth() + 10, modOneWaveSelect.getY() + modOneWaveSelect.getHeight() / 4, 150, 20);

    modOneFreqSlider.setBounds(0, (getHeight()/2)+64, 70, 100); 
    modOneIntSlider.setBounds(70, (getHeight()/2)+64, 70, 100);
}

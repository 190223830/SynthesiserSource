/*
  ==============================================================================

    Osc.cpp
    Created: 2 Feb 2022 3:49:21pm
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Osc.h"

Osc::Osc(juce::AudioProcessorValueTreeState& valueTreeState, juce::String wave, juce::String modOneFreqID, juce::String modOneIntID)
{
    juce::StringArray waves{ "Sine", "Saw", "Square"};
    waveSelect.addItemList(waves, 1);
    addAndMakeVisible(waveSelect);
    waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTreeState, wave, waveSelect);

    modOneFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modOneFreqSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    modOneIntSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modOneIntSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    
    addAndMakeVisible(modOneFreqSlider);
    modOneFreqLabel.setFont(15.0f);
    modOneFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modOneFreqLabel);

    addAndMakeVisible(modOneIntSlider);
    modOneIntLabel.setFont(15.0f);
    modOneIntLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modOneIntLabel);
    
    modOneFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "MODONEFREQ", modOneFreqSlider);
    modOneIntAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "MODONEINT", modOneIntSlider);
}

Osc::~Osc()
{
}

void Osc::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    /*g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());*/

}

void Osc::resized()
{
    waveSelect.setBounds(15, getHeight()/2, 100, 40);

    modOneFreqSlider.setBounds(0, (getHeight()/2)+64, 70, 100); //TODO: create a new class/component that has a constructor that does all of this
    modOneFreqLabel.setBounds(modOneFreqSlider.getX(), modOneFreqSlider.getY()+ modOneFreqSlider.getHeight(), modOneFreqSlider.getWidth(), 20);

    modOneIntSlider.setBounds(70, (getHeight()/2)+64, 70, 100);
    modOneIntLabel.setBounds(modOneIntSlider.getX(), modOneIntSlider.getY()+ modOneIntSlider.getHeight(), modOneIntSlider.getWidth(), 20);
}

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

    modOneFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modOneFreqSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    modOneIntSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    modOneIntSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    
    addAndMakeVisible(modOneFreqSlider);
    addAndMakeVisible(modOneIntSlider);
    
    modOneFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "MODONEFREQ", modOneFreqSlider);
    modOneIntAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "MODONEINT", modOneIntSlider);
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
    waveSelect.setBounds(0, getHeight()/2-20, 100, 40);
    modOneFreqSlider.setBounds(0, (getHeight()/2)+50, 50, 100);
    modOneIntSlider.setBounds(50, getHeight()/2+50, 50, 100);
}

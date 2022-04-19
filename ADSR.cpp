/*
  ==============================================================================

    ADSR.cpp
    Created: 2 Feb 2022 10:16:55am
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSR.h"

ADSR::ADSR(juce::AudioProcessorValueTreeState& valueTreeState,
    juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID,
    juce::String modulationTarget)

    : attackSlider("Attack", attackID, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag), 
    decaySlider("Decay", decayID, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    sustainSlider("Sustain", sustainID, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    releaseSlider("Release", releaseID, valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    //TODO: Add modulation target changing

    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
}

ADSR::~ADSR()
{
}

void ADSR::paint (juce::Graphics& g)
{
 

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (juce::Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ADSR::resized()
{

    attackSlider.setBounds(0, 0, 75, 100);
    decaySlider.setBounds(attackSlider.getRight(), 0, 75, 100);
    sustainSlider.setBounds(decaySlider.getRight(), 0, 75, 100);
    releaseSlider.setBounds(sustainSlider.getRight(), 0, 75, 100);

}

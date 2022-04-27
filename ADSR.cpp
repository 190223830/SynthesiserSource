/*
  ==============================================================================

    ADSR.cpp
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
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
}

ADSR::~ADSR() {}
void ADSR::paint (juce::Graphics& g) {}

void ADSR::resized()
{

    attackSlider.setBounds(0, 0, 70, 75);
    decaySlider.setBounds(attackSlider.getRight(), 0, 70, 75);
    sustainSlider.setBounds(decaySlider.getRight(), 0, 70, 75);
    releaseSlider.setBounds(sustainSlider.getRight(), 0, 70, 75);

}

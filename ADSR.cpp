/*
  ==============================================================================

    ADSR.cpp
    Created: 2 Feb 2022 10:16:55am
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSR.h"

ADSR::ADSR(juce::AudioProcessorValueTreeState& valueTreeState)
{

    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, "RELEASE", releaseSlider);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);     //TODO: make a method for this to keep the code dry
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

    attackSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);

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
    const auto adsrSection = getLocalBounds();
    const auto adsrPadding = 10;
    const auto adsrSliderWidth = adsrSection.getWidth() / 4 - adsrPadding;
    const auto adsrSliderHeight = adsrSection.getHeight();
    const auto adsrSliderX = 0;
    const auto adsrSliderY = 0;

    attackSlider.setBounds(adsrSliderX, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);

}

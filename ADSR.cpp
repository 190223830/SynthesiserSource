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
{
    //TODO: Add modulation target changing

    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, attackID, attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, decayID, decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, sustainID, sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(valueTreeState, releaseID, releaseSlider);


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

    attackLabel.setFont(15.0f);
    attackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(attackLabel);

    decayLabel.setFont(15.0f);
    decayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayLabel);

    sustainLabel.setFont(15.0f);
    sustainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sustainLabel);

    releaseLabel.setFont(15.0f);
    releaseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(releaseLabel);
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
    const auto adsrSliderHeight = adsrSection.getHeight()-50;
    const auto adsrSliderX = 0;
    const auto adsrSliderY = 0;

    attackSlider.setBounds(adsrSliderX, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() + attackSlider.getHeight(), attackSlider.getWidth(), 20);

    decaySlider.setBounds(attackSlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getY() + decaySlider.getHeight(), decaySlider.getWidth(), 20);
    
    sustainSlider.setBounds(decaySlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getY() + sustainSlider.getHeight(), sustainSlider.getWidth(), 20);
    
    releaseSlider.setBounds(sustainSlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() + releaseSlider.getHeight(), releaseSlider.getWidth(), 20);

}

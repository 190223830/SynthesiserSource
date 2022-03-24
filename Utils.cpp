/*
  ==============================================================================

    Utils.cpp
    Created: 24 Mar 2022 6:03:27am
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Utils.h"


using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using SliderStyle = juce::Slider::SliderStyle;

GenericSlider::GenericSlider(juce::String labelName, juce::String parameter, juce::AudioProcessorValueTreeState& apvts, SliderStyle style)
{
    slider.setSliderStyle(style);
    slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(slider);

    label.setFont(fontSize);
    label.setText(labelName, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    attachment = std::make_unique<SliderAttachment>(apvts, parameter, slider);
}

void GenericSlider::resized()
{
    slider.setBounds(0, 0, sliderWidth, sliderHeight);
    label.setBounds(0, sliderHeight, sliderWidth, labelHeight);   
}


Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::paint(juce::Graphics& g)
{
    //add in colour scheme here
}

void Utils::resized()
{
}
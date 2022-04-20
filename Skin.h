/*
  ==============================================================================

    Skin.h
    Created: 20 Apr 2022 12:02:31pm
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <juceHeader.h>
    class Skin : public juce::LookAndFeel_V4
    {
    public:
        void Skin::drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
            float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&);
    private:
        juce::Label* createSliderTextBox(juce::Slider& slider) override;
        juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;
    };
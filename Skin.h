/*
  ==============================================================================

    Skin.h
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
        void drawComboBox(juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) override;
        juce::Font getComboBoxFont(juce::ComboBox& box) override;
        void positionComboBoxText(juce::ComboBox& box, juce::Label& label) override;
    };
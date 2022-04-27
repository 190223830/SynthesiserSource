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
        /// <summary>
        /// Draws a new rotary slider.
        /// </summary>
        /// <param name=""></param>
        /// <param name="x">Left X-axis value</param>
        /// <param name="y">Top y-axis value</param>
        /// <param name="width">Width of slider</param>
        /// <param name="height">Height of slider</param>
        /// <param name="sliderPos">Radius</param>
        /// <param name="rotaryStartAngle">Start of slider arc</param>
        /// <param name="rotaryEndAngle">End of slider arc</param>
        /// <param name="">Slider name</param>
        void Skin::drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
            float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&);
    private:
        /// <summary>
        /// Creates a text box for a given slider.
        /// </summary>
        /// <param name="slider">Slider</param>
        /// <returns></returns>
        juce::Label* createSliderTextBox(juce::Slider& slider) override;
        juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;

        /// <summary>
        /// Draws a new ComboBox object.
        /// </summary>
        /// <param name="g">Name</param>
        /// <param name="width">Width</param>
        /// <param name="height">Height</param>
        void drawComboBox(juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) override;

        /// <summary>
        /// Gets the font of a ComboBox.
        /// </summary>
        /// <param name="box">ComboBox</param>
        /// <returns>Font</returns>
        juce::Font getComboBoxFont(juce::ComboBox& box) override;

        /// <summary>
        /// Repositions the ComboBox text.
        /// </summary>
        /// <param name="box">ComboBox</param>
        /// <param name="label">ComboBox text box</param>
        void positionComboBoxText(juce::ComboBox& box, juce::Label& label) override;
    };
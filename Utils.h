/*
  ==============================================================================

    Utils.h
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Skin.h"

static constexpr float fontSize{ 10.0f };

class Utils : public juce::Component
{
public:
    Utils();
    ~Utils() override;

    /// <summary>
    /// Re-skins the component.
    /// </summary>
    void paint(juce::Graphics&) override;

    /// <summary>
    /// How the component will be laid out on screen.
    /// </summary>
    void resized() override;

    /// <summary>
    /// Sets the name of a component.
    /// </summary>
    /// <param name="name">Component name</param>
    void setName(juce::String name) { thisName = name; }

private:
    juce::String thisName{""};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Utils)
};

class GenericSlider : public juce::Component
{
public:
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using SliderStyle = juce::Slider::SliderStyle;

    GenericSlider(juce::String labelName, juce::String parameter, juce::AudioProcessorValueTreeState& valueTreeState, SliderStyle style = SliderStyle::RotaryHorizontalVerticalDrag);
    ~GenericSlider() override;


    /// <summary>
    /// How the component will be laid out on screen.
    /// </summary>
    void resized() override;

private:
    Skin skin;
    static constexpr int textBoxWidth{ 50 }, textBoxHeight{ 20 }, labelHeight{ 20 };
    int sliderWidth{ 70 }, sliderHeight{ 70 };
    juce::Slider slider;
    juce::Label label;
    std::unique_ptr<SliderAttachment> attachment;
};

class Visualiser : public juce::AudioVisualiserComponent {
public:
    Visualiser() : AudioVisualiserComponent(2) {
        setBufferSize(128);
        setSamplesPerBlock(16);
        setColours(juce::Colours::black, juce::Colours::darkturquoise);
    };
};

class SynthesiserPlusAddons : public juce::Synthesiser {
public:
    /// <summary>
    /// Overrides JUCE method to play note when a note is pressed, loops through several notes to allow for unison.
    /// </summary>
    /// <param name="midiChannel">MIDI Channel</param>
    /// <param name="midiNoteNumber">Note pressed</param>
    /// <param name="velocity">Speed of note pressed on keyboard input</param>
    void noteOn(const int midiChannel,
        const int midiNoteNumber,
        const float velocity) override;

    /// <summary>
    /// Sets the number of voices to be played every time a note is pressed.
    /// </summary>
    /// <param name="unisonId">Value Tree Parameter</param>
    void setUnisonNo(const int unisonId);

    /// <summary>
    /// Removes voices from Synth as per user input.
    /// </summary>
    /// <param name="voicesToRemove">Number of voices to be removed</param>
    void removeVoices(const int voicesToRemove);

private:
    int unisonNo = 1;
};

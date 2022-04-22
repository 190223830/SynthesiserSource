/*
  ==============================================================================

    Utils.h
    Created: 24 Mar 2022 6:03:27am
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
    void paint(juce::Graphics&) override;
    void resized() override;

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
    void noteOn(const int midiChannel,
        const int midiNoteNumber,
        const float velocity) override;

    void setUnisonNo(const int unisonId);
    void removeVoices(const int voicesToRemove);

private:
    int unisonNo = 1;
};

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSR.h"
#include "Osc.h"

class SynthOneAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthOneAudioProcessorEditor (SynthOneAudioProcessor&);
    ~SynthOneAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // This reference is provided as a quick way for your editor to access the processor object that created it
    SynthOneAudioProcessor& audioProcessor;

    ADSR adsr;
    Osc osc;

    juce::Slider gainSlider;
    //juce::ComboBox waveSelect;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    juce::Label gainLabel{ "gainLabel", "Gain" };
    //std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthOneAudioProcessorEditor)
};

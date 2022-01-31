#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    //juce::Slider gainSlider;
    juce::ComboBox waveSelect;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    //std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthOneAudioProcessorEditor)
};

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSR.h"
#include "Osc.h"
#include "Filter.h"
#include "Utils.h"
#include "LFO.h"

class SynthOneAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthOneAudioProcessorEditor (SynthOneAudioProcessor&);
    ~SynthOneAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    void setVisualiser();
    // This reference is provided as a quick way for your editor to access the processor object that created it
    SynthOneAudioProcessor& audioProcessor;

    ADSR adsr;
    Osc osc;
    Osc osc2;
    Filter filter;
    ADSR egAdsr;
    LFO lfo1, lfo2;
    Visualiser visualiserToShow;

    //juce::Slider gainSlider;
    GenericSlider gainSlider, gain2Slider;
    //juce::ComboBox waveSelect;

    //std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    //juce::Label gainLabel{ "gainLabel", "Gain" };
    //std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthOneAudioProcessorEditor)
};

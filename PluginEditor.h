#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSR.h"
#include "Osc.h"
#include "Filter.h"
#include "Utils.h"
#include "LFO.h"
#include "FilterVisualiser.h"

class SynthOneAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthOneAudioProcessorEditor (SynthOneAudioProcessor&);
    ~SynthOneAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    //void setVisualiser();
    // This reference is provided as a quick way for your editor to access the processor object that created it
    SynthOneAudioProcessor& audioProcessor;

    ADSR adsr0, adsr1, adsr2, adsr3;
    Osc osc0, osc1, osc2, osc3;
    Filter filter;
    ADSR egAdsr;
    LFO lfo1, lfo2;
    Visualiser visualiserToShow;
    FilterVisualiser filterVisualiser;

    //juce::Slider gainSlider;
    GenericSlider gainSlider0, gainSlider1, gainSlider2, gainSlider3;
    GenericSlider detuneSlider0, detuneSlider1, detuneSlider2, detuneSlider3;
    GenericSlider courseTuneSlider0, courseTuneSlider1, courseTuneSlider2, courseTuneSlider3;
    GenericSlider panSlider0, panSlider1, panSlider2, panSlider3;
    GenericSlider voiceSlider, unisonSlider;

    juce::MidiKeyboardComponent keyboard;
    //juce::ComboBox waveSelect;

    //std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    //juce::Label gainLabel{ "gainLabel", "Gain" };
    //std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthOneAudioProcessorEditor)
};

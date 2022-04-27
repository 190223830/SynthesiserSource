#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSR.h"
#include "Osc.h"
#include "Filter.h"
#include "Utils.h"
#include "LFO.h"
#include "FilterVisualiser.h"
#include "Matrix.h"

class SynthOneAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthOneAudioProcessorEditor (SynthOneAudioProcessor&);
    ~SynthOneAudioProcessorEditor() override;

    /// <summary>
    /// Re-skins the component.
    /// </summary>
    void paint (juce::Graphics&) override;

    /// <summary>
    /// How the component will be laid out on screen.
    /// </summary>
    void resized() override;

    

private:
    SynthOneAudioProcessor& audioProcessor;

    ADSR adsr0, adsr1, adsr2, adsr3;
    Osc osc0, osc1, osc2, osc3;
    Filter filter;
    ADSR egAdsr;
    LFO lfo1, lfo2;

    GenericSlider gainSlider0, gainSlider1, gainSlider2, gainSlider3;
    GenericSlider detuneSlider0, detuneSlider1, detuneSlider2, detuneSlider3;
    GenericSlider courseTuneSlider0, courseTuneSlider1, courseTuneSlider2, courseTuneSlider3;
    GenericSlider panSlider0, panSlider1, panSlider2, panSlider3;
    GenericSlider voiceSlider, unisonSlider;

    Matrix* matrix = Matrix::getInstance();

    juce::MidiKeyboardComponent keyboard;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthOneAudioProcessorEditor)
};

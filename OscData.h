/*
  ==============================================================================

    oscData.h
    Created: 2 Feb 2022 3:15:58pm
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "LFOData.h"

class OscData : public juce::dsp::Oscillator<float> {
public:
    void OscData::setWaveType(const int waveType);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void processBlock(juce::dsp::AudioBlock<float>& block);
    void OscData::setFreq(const int midiNoteNumber, const int detune, const int courseTune, float modOne=0.0f);
    void setModulator(LFOData* modOsc);

private:
    LFOData* modulatorOsc;
    bool called = false;
    float modulator{ 0.0f };
    float modulatorInt{ 0.0f };
    int midiNote{0};
    float detuneInHertz{ 0.00f };
    float modTotal{ 0.0f };
};
/*
  ==============================================================================

    VirtualOsc.h
    Created: 20 Apr 2022 7:44:30pm
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VirtualOsc : public virtual juce::dsp::Oscillator<float> {
public:
    virtual void setWaveType(const int waveType) {}
    virtual float processBlock(juce::dsp::AudioBlock<float>& block) { return 0; }
    virtual void setFreq(const float rate) {}
    virtual void setParams(float lfoRate, float lfoInt, int lfoWaveType) {}

    virtual void prepareToPlay(juce::dsp::ProcessSpec& spec) {}
    virtual void setFreq(const int midiNoteNumber, const int detune, const int courseTune) {}
    virtual void setModulator(VirtualOsc* modOsc, int modNum) {}
    virtual void updateModulator() {}
    virtual void removeModulator(VirtualOsc* modOsc) {}

private:


};
/*
  ==============================================================================

    oscData.h
    Created: 2 Feb 2022 3:15:58pm
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "VirtualOsc.h"

class OscData : public VirtualOsc {
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    float processBlock(juce::dsp::AudioBlock<float>& block);
    void setFreq(const int midiNoteNumber, const int detune, const int courseTune);
    void setModulator(VirtualOsc* modOsc, int modNum);
    void updateModulator();
    void removeModulator(VirtualOsc* modOsc);
    void setParams(float lfoRate, float lfoInt, int lfoWaveType);
    void setAsMod(bool status);
    

private:
    static constexpr auto modulators = 6;
    VirtualOsc* modulatorOsc[modulators];
    bool modCalled[modulators];
    float modValue{ 0.000f };
    int midiNote{0};
    float detuneInHertz{ 0.00f };
    float currentFreq{ 0.0f };
    bool thisIsModulator = false;
    
};
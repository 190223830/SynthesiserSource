/*
  ==============================================================================

    oscData.h
    Created: 2 Feb 2022 3:15:58pm
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> {
public:
    void OscData::setWaveType(const int waveType);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void processBlock(juce::dsp::AudioBlock<float>& block);
    void OscData::setFreq(const int midiNoteNumber);

private:


};
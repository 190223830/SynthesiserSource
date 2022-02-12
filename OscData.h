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

    void setModParams(const float intensity, const float freq);

private:
    juce::dsp::Oscillator<float>modOneOsc{ [](float x) {return std::sin(x); } }; //TODO: call setWaveType() here
    float modOne{ 0.0f };
    float modOneInt{ 0.0f };
    int midiNote{0};
};
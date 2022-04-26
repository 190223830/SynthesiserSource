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
<<<<<<< Updated upstream
    void OscData::setWaveType(const int waveType);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void processBlock(juce::dsp::AudioBlock<float>& block);
    void OscData::setFreq(const int midiNoteNumber, const int detune, const int courseTune);

    void setModParams(const float intensity, const float freq, const int waveType);

private:
    juce::dsp::Oscillator<float>modOneOsc;
    //juce::dsp::Oscillator<float>modOneOsc{ [](float x) {return std::sin(x); } }; //TODO: call setWaveType() here
    float modOne{ 0.0f };
    float modOneInt{ 0.0f };
=======
    //void setWaveType(const int waveType);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    float processBlock(juce::dsp::AudioBlock<float>& block);
    void setFreq(const int midiNoteNumber, const int detune, const int courseTune);
    void setModulator(VirtualOsc* modOsc, int modNum);
    void updateModulator();
    void removeModulator(VirtualOsc* modOsc);
    void setParams(float lfoRate, float lfoInt, int lfoWaveType);

private:
    static constexpr auto modulators = 6;
    VirtualOsc* modulatorOsc[modulators];
    bool modCalled[modulators];
    float modValue{ 0.000f };
>>>>>>> Stashed changes
    int midiNote{0};
    float detuneInHertz{ 0.00f };
    float modTotal{ 0.0f };
};
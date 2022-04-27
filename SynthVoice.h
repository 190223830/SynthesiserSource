/*
  ==============================================================================

    SynthVoice.h
    Created: 31 Jan 2022 5:40:27am
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "ADSRData.h"
#include "OscData.h"
#include "FilterData.h"
#include "LFOData.h"
#include "Matrix.h"

class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int ControllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void pitchWheelMoved(int newPitchWheelValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void update(const float attack, const float decay, const float sustain, const float release);
    void updateGain(const float gainValue);
    void updateDetune(const int detuneValue, const int courseTuneValue);
    OscData& getOsc();
    //LFOData& getLFO() { return lfo; };
    void updateFilter(const int filterType, const float filterCutoff, const float filterResonance, const float intensity);
    void updateEGADSR(const float attack, const float decay, const float sustain, const float release);
    void setPanValue(const float pan);
    float getModulatedFilterCutoff();
    void setLFO(int lfoNo, float lfoRate, float lfoInt, int lfoWaveType, int oscNum);
    void setFM(int modOsc, int destOsc, OscData* osc);

private:
    juce::dsp::ProcessSpec spec;
    Matrix* matrix = Matrix::getInstance();
    ADSRData adsr;
    OscData osc;
    int detune{ 0 }, courseTune{ 0 };
    juce::dsp::Panner<float> panner;
    FilterData filter;
    ADSRData egADSR;
    LFOData lfo1, lfo2;
    juce::AudioBuffer<float> oscBuffer;
                        
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};


};

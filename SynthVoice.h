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

class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int ControllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void pitchWheelMoved(int newPitchWheelValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    juce::AudioBuffer<float> oscBuffer;

    juce::dsp::Oscillator<float> oscSin{ [](float x) {return std::sin(x); } };                              //sine wave
    juce::dsp::Oscillator<float> oscSaw{ [](float x) {return x / juce::MathConstants<float>::pi; } };         //saw wave
    juce::dsp::Oscillator<float> oscSqu{ [](float x) {return x < 0.0f ? -1.0f : 1.0f; } };                     //square wave

    juce::dsp::Gain<float> gain;
    bool isPrepared {false};


};

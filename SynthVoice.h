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
//#include "LFO.h"

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
    void updateGain(const float gain);
    OscData& getOsc() { return osc; };
    void updateFilter(const int filterType, const float filterCutoff, const float filterResonance, const float intensity);
    void updateEGADSR(const float attack, const float decay, const float sustain, const float release);

private:
    //juce::ADSR adsr;
    ADSRData adsr;
    OscData osc;
    FilterData filter;
    ADSRData egADSR;
    juce::dsp::Oscillator<float> lfo; //Create new LFOData class and move/inherit the stuff from OscData, or try and use OscData (but that sounds like it's gonna suck)

    juce::AudioBuffer<float> oscBuffer;
                        
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};


};

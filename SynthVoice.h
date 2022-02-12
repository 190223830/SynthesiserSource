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

private:
    //juce::ADSR adsr;
    ADSRData adsr;
    OscData osc;

    juce::AudioBuffer<float> oscBuffer;
                        
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};

    //This may need to go in the SynthVoice class
    enum FilterType { LPF, BPF, HPF };
    juce::dsp::StateVariableTPTFilter<float> filter; // TODO: look at creating own filter with different dB/Oct types
    void filterReset(); //override;
    void setType();
    FilterType filterType{ FilterType::LPF };


};

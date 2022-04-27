/*
  ==============================================================================

    oscData.h
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "VirtualOsc.h"
#include "LFOData.h"

class OscData : public VirtualOsc {
public:
    /// <summary>
    /// Sets the 'resolution' of the component, and how often it should pass to the output.
    /// </summary>
    /// <param name="sampleRate"> How often does the parameter register a change </param>
    /// <param name="samplesPerBlock"> How often should the component output </param>
    /// <param name="outputChannels"> Number of audio channels to output to (Right/Left) </param>
    void prepareToPlay(juce::dsp::ProcessSpec& spec);

    /// <summary>
    /// Processes input values into floats suitable for audio output.
    /// </summary>
    /// <param name="block">Block of sample data</param>
    /// <returns>Audio data</returns>
    float processBlock(juce::dsp::AudioBlock<float>& block);

    /// <summary>
    /// Sets frequency.
    /// </summary>
    void setFreq(const int midiNoteNumber, const int detune, const int courseTune);

    /// <summary>
    /// Sets the Oscillator that will modulate this Oscillator's output signal.
    /// </summary>
    void setModulator(VirtualOsc* modOsc, int modNum);

    /// <summary>
    /// Polls the oscillator to update its frequency based on modulator information.
    /// </summary>
    void updateModulator();


    void removeModulator(VirtualOsc* modOsc);

    /// <summary>
    /// Empty function to override abstract class VirtualOsc.
    /// </summary>
    void setParams(float lfoRate, float lfoInt, int lfoWaveType);

    /// <summary>
    /// Defines whether this Oscillator is a modulator of another Oscillator.
    /// </summary>
    /// <param name="status"> Whether this is a modulator or not</param>
    //void setAsMod(bool status);
    

private:
    static constexpr auto modulators = 2; //should be six if everything was working
    VirtualOsc* modulatorOsc[modulators];
    bool modCalled[modulators];
    float modValue{ 0.000f };
    int midiNote{0};
    float detuneInHertz{ 0.00f };
    float currentFreq{ 0.0f };
    //bool thisIsModulator = false;
    
};
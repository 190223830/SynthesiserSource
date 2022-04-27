/*
  ==============================================================================

    VirtualOsc.h
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VirtualOsc : public virtual juce::dsp::Oscillator<float> {
public:
    /// <summary>
    /// Sets the wave type of a given Oscillator.
    /// </summary>
    /// <param name="waveType"> Sine, Saw, Square </param>
    virtual void setWaveType(const int waveType) {
        switch ((int)waveType)
        {
        case 0:
            initialise([](float x) {return std::sin(x); });
            break;
        case 1:
            initialise([](float x) {return x / juce::MathConstants<float>::pi; });
            break;
        case 2:
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
            break;
        default:
            jassertfalse; //error
            break;
        }
    }

    /// <summary>
    /// (OVERRIDDEN) Processes input values into floats suitable for audio output
    /// </summary>
    /// <param name="block">Block of sample data</param>
    /// <returns>Audio data</returns>
    virtual float processBlock(juce::dsp::AudioBlock<float>& block) { return 0; }

    /// <summary>
    /// (OVERRIDDEN) Sets frequency.
    /// </summary>
    //virtual void setFreq(const float rate) {}
    virtual void setFreq(const int midiNoteNumber, const int detune, const int courseTune) {}

    /// <summary>
    /// (OVERRIDDEN) Sets LFO parameters. 
    /// </summary>
    virtual void setParams(float lfoRate, float lfoInt, int lfoWaveType) {}

    /// <summary>
    /// (OVERRIDDEN) Sets the 'resolution' of the component, and how often it should pass to the output. 
    /// </summary>
    /// <param name="sampleRate"> How often does the parameter register a change </param>
    /// <param name="samplesPerBlock"> How often should the component output </param>
    /// <param name="outputChannels"> Number of audio channels to output to (Right/Left) </param>
    virtual void prepareToPlay(juce::dsp::ProcessSpec& spec) {}

    /// <summary>
    /// (OVERRIDDEN) Sets the Oscillator that will modulate this Oscillator's output signal.
    /// </summary>
    virtual void setModulator(VirtualOsc* modOsc, int modNum) {}

    /// <summary>
    /// (OVERRIDDEN) Polls the oscillator to update its frequency based on modulator information.
    /// </summary>
    virtual void updateModulator() {}

    /// <summary>
    /// Removes modulator.
    /// </summary>
    virtual void removeModulator(VirtualOsc* modOsc) {}

private:


};
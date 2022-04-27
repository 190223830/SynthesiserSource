/*
  ==============================================================================

    FilterData.h
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "FilterVisualiser.h"

class FilterData {
public:
    /// <summary>
    /// Sets the 'resolution' of the component, and how often it should pass to the output.
    /// </summary>
    /// <param name="sampleRate"> How often does the parameter register a change </param>
    /// <param name="samplesPerBlock"> How often should the component output </param>
    /// <param name="outputChannels"> Number of audio channels to output to (Right/Left) </param>
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    /// <summary>
    /// Outputs block to buffer.
    /// </summary>
    /// <param name="buffer"> Buffer to output to </param>
    void prepare(juce::AudioBuffer<float>& buffer);
    void reset();

    /// <summary>
    /// Updates filter paramaters.
    /// </summary>
    /// <param name="type"> LPF, BPF, HPF </param>
    /// <param name="cutoff"> Filter Cutoff </param>
    /// <param name="resonance"> Filter resonance </param>
    /// <param name="intensity"> EG intensity </param>
    /// <param name="mod"> EG mod value </param>
    void updateParams(const int type, float cutoff, float resonance, const float intensity, const float mod = 1.0f);

    /// <summary>
    /// Returns current cutoff position after being modulated.
    /// </summary>
    /// <returns> Filter cutoff + modulation </returns>
    float getModulatedCutoff();
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter; // TODO: look at creating own filter with different dB/Oct types
    float modulatedCutoffWithinBounds;
};
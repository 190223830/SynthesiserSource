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
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void prepare(juce::AudioBuffer<float>& buffer);
    void reset();


    void updateParams(const int type, float cutoff, float resonance, const float intensity, const float mod = 1.0f);
    float getModulatedCutoff();
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter; // TODO: look at creating own filter with different dB/Oct types
    float modulatedCutoffWithinBounds;
};
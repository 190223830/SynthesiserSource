/*
  ==============================================================================

    FilterData.h
    Created: 12 Feb 2022 12:10:59pm
    Author:  ellio

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData {
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void prepare(juce::AudioBuffer<float>& buffer);
    void reset();


    void updateParams(const int type, float cutoff, float resonance, const float intensity, const float mod = 1.0f);
    

private:
    juce::dsp::StateVariableTPTFilter<float> filter; // TODO: look at creating own filter with different dB/Oct types

    //enum FilterType { LPF, BPF, HPF };
    //FilterType filterType{ FilterType::LPF };
};
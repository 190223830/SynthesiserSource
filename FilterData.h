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
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void prepare(juce::AudioBuffer<float>& buffer);
    void reset();


    void updateParams(const int type, float cutoff, float resonance);

private:

};
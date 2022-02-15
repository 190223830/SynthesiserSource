/*
  ==============================================================================

    FilterData.cpp
    Created: 12 Feb 2022 12:10:59pm
    Author:  ellio

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    //reset();
    filter.prepare(spec);
    
}

void FilterData::reset() {
    filter.reset();
}

void FilterData::updateParams(const int type, float cutoff, float resonance, const float mod) {

    using filterType = juce::dsp::StateVariableTPTFilterType; //TODO: use this to clean up everything
    switch (type)
    {
    case 0:
        filter.setType(filterType::lowpass);
        break;
    case 1:
        filter.setType(filterType::bandpass);
        break;
    case 2:
        filter.setType(filterType::highpass);
        break;
    default:
        jassertfalse; //error
        break;
    }

    float modulatedCutoff = std::fmin(std::fmax(mod * cutoff, 20.0f), 20000.0f); //sets upper and lower bounds for cutoff

    filter.setCutoffFrequency(modulatedCutoff);
    filter.setResonance(resonance);
    
}

void FilterData::prepare(juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

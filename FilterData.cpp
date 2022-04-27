/*
  ==============================================================================

    FilterData.cpp
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
    filter.prepare(spec);
    
}

void FilterData::reset() {
    filter.reset();
}

void FilterData::updateParams(const int type, float cutoff, float resonance, const float intensity, const float mod) {

    using filterType = juce::dsp::StateVariableTPTFilterType;
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

    float dInt = intensity * mod     *cutoff;
    float modulatedCutoff = cutoff + dInt;

    modulatedCutoffWithinBounds = std::fmin(std::fmax(modulatedCutoff, 20.0f), 20000.0f); //sets upper and lower bounds for cutoff
    filter.setCutoffFrequency(modulatedCutoffWithinBounds);
    filter.setResonance(resonance);
    
}

void FilterData::prepare(juce::AudioBuffer<float>& buffer) {
    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

float FilterData::getModulatedCutoff() { return modulatedCutoffWithinBounds; }
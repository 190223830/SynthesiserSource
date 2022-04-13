/*
  ==============================================================================

    SynthVoice.cpp
    Created: 31 Jan 2022 5:40:27am
    Author:  ellio

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
};
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {

    osc.setFreq(midiNoteNumber);
    osc2.setFreq(midiNoteNumber);
    adsr.noteOn();
    egADSR.noteOn();
};
void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
    egADSR.noteOff();
    if (!adsr.isActive()) {
        clearCurrentNote(); //if envelope is finished, no need to output
        adsr.reset();
    };
    
};
void SynthVoice::controllerMoved(int ControllerNumber, int newControllerValue) {

};
void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    jassert(isPrepared);

    if (!isVoiceActive()) {
        return;     //if nothing is playing, no need to output
    };

    //clear outputBuffer to realign phase of osc - fixes clicking sound on attack and release
    oscBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    egADSR.applyEnvelopeToBuffer(oscBuffer, 0, numSamples);
    oscBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock{ oscBuffer };

    //juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };
    osc.processBlock(audioBlock);
    osc2.processBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    filter.prepare(oscBuffer);
    

    //adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    adsr.applyEnvelopeToBuffer(oscBuffer, 0, oscBuffer.getNumSamples());
    

    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
        outputBuffer.addFrom(channel, startSample, oscBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) {
            clearCurrentNote(); //if envelope is finished, no need to output
        };
    };

    
    
};

void SynthVoice::updateFilter(const int filterType, const float filterCutoff, const float filterResonance, const float intensity) {
    float mod = egADSR.getNextSample();
    filter.updateParams(filterType, filterCutoff, filterResonance, intensity, mod);
}

void SynthVoice::updateEGADSR(const float attack, const float decay, const float sustain, const float release) {
    egADSR.updateADSR(attack, decay, sustain, release);
}


void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {

};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    adsr.setSampleRate(sampleRate);
    osc.prepareToPlay(spec);
    osc2.prepareToPlay(spec);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    gain.prepare(spec);
    gain2.prepare(spec);
    egADSR.setSampleRate(sampleRate);
    //lfo.prepare(spec);
    //lfo.initialise([](float x) { return std::sin(x); });

    

    isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateGain(const float gainValue, const float gain2Value) {    //TODO: Incorporate into update method
    gain.setGainLinear(gainValue);
    gain2.setGainLinear(gain2Value);
}


OscData& SynthVoice::getOsc(int i) {
    switch (i) {
    case 1:
        return osc;
    case 2:
        return osc2;
    default:
        jassertfalse;
    }
}



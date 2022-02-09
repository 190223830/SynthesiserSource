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
    adsr.noteOn();
};
void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
    if (!adsr.isActive() || !allowTailOff) {
        clearCurrentNote(); //if envelope is finished, no need to output
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
    oscBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock{ oscBuffer };

    //juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };
    osc.processBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    //adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    adsr.applyEnvelopeToBuffer(oscBuffer, 0, oscBuffer.getNumSamples());
    

    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
        outputBuffer.addFrom(channel, startSample, oscBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) {
            clearCurrentNote(); //if envelope is finished, no need to output
        };
    };
};

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {

};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    adsr.setSampleRate(sampleRate);

    osc.prepareToPlay(spec);
    gain.prepare(spec);

    isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateGain(const float gainValue) {    //TODO: Incorporate into update method
    gain.setGainLinear(gainValue);
}

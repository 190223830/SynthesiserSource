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
    oscSin.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
};
void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
};
void SynthVoice::controllerMoved(int ControllerNumber, int newControllerValue) {

};
void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };
    oscSin.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
};
void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {

};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    adsr.setSampleRate(sampleRate);

    oscSin.prepare(spec);
    gain.prepare(spec);

    gain.setGainLinear(0.5f);
    //oscSin.setFrequency(440.0f);


    isPrepared = true;
}

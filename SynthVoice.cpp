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
    lfo1.reset();
    lfo2.reset();
    osc.setFreq(midiNoteNumber, detune, courseTune);
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

void SynthVoice::controllerMoved(int ControllerNumber, int newControllerValue) {};

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {

    //while (!isPrepared);
    jassert(isPrepared);

    if (!isVoiceActive()) {
        return;     //if nothing is playing, no need to output
    };

    //clear outputBuffer to realign phase of osc - fixes clicking sound on attack and release
    oscBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    egADSR.applyEnvelopeToBuffer(oscBuffer, 0, numSamples);
    oscBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock{ oscBuffer };
    osc.processBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    filter.prepare(oscBuffer);
    panner.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
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

void SynthVoice::updateDetune(const int detuneValue, const int courseTuneValue) {
    detune = detuneValue;
    courseTune = courseTuneValue;
}


void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {

};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    adsr.setSampleRate(sampleRate);
    osc.prepareToPlay(spec);
    lfo1.prepare(spec);
    lfo2.prepare(spec);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    gain.prepare(spec);
    egADSR.setSampleRate(sampleRate);
    panner.prepare(spec);
    
    isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateGain(const float gainValue) {
    gain.setGainLinear(gainValue);
}

void SynthVoice::setPanValue(float pan) {
    panner.setPan(pan);
}

OscData& SynthVoice::getOsc() {
    return osc;
}

float SynthVoice::getModulatedFilterCutoff() {
    return filter.getModulatedCutoff();
}

void SynthVoice::setLFO(int lfoNum, float lfoRate, float lfoInt, int lfoWaveType, int oscNum) {
    if(matrix->getValue((oscNum+3)%4, 3+lfoNum)) {
        switch (lfoNum) {
        case 1:
            lfo1.setParams(lfoRate, lfoInt, lfoWaveType);
            getOsc().setModulator(&lfo1, lfoNum-1);
            break;
        case 2:
            lfo2.setParams(lfoRate, lfoInt, lfoWaveType);
            getOsc().setModulator(&lfo2, lfoNum-1);                         //TODO: MAKE ADD MODULATOR METHOD WITH MODULATOR ARRAY, THIS WILL CURRENTLY OVERWRITE LFO1
            break;
        default:
            jassertfalse;
            break;
        }
    }
    else {
        switch (lfoNum) {
        case 1:
            getOsc().removeModulator(&lfo1);
            break;
        case 2:
            getOsc().removeModulator(&lfo2);
            break;
        default:
            jassertfalse;
            break;
        }
    }
}

void SynthVoice::setFM(int modOsc, int destOsc, OscData* osc) {
    if (matrix->getValue((destOsc + 3) % 4, (modOsc + 3) % 4)) {
        osc->setAsMod(true);
        getOsc().setModulator(osc, (modOsc + 3) % 4);
    }
    else {
        //osc->setAsMod(true);
        getOsc().removeModulator(osc);
    }
}


/*
  ==============================================================================

    oscData.cpp
    Author:  ellio

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
    for (int i = 0; i < modulators; i++) {
        if (modCalled[i]) {
            //if (auto osc = dynamic_cast<OscData*>(modulatorOsc[i])) osc->prepare(spec);
        }
    }
    prepare(spec);
}

float OscData::processBlock(juce::dsp::AudioBlock<float>& block) {
    //if (thisIsModulator) return processSample(block.getSample(0, 0));
    float temp = 0.0f;
    for (int i = 0; i < modulators; i++) if (modCalled[i]) temp += modulatorOsc[i]->processBlock(block);
    modValue = temp;
    process(juce::dsp::ProcessContextReplacing<float>(block));
    return 0;
}

void OscData::setFreq(const int midiNoteNumber, const int detuneValue, const int courseTuneValue) {
    midiNote = midiNoteNumber + courseTuneValue;
    detuneInHertz = detuneValue * ((juce::MidiMessage::getMidiNoteInHertz(midiNote) - juce::MidiMessage::getMidiNoteInHertz(midiNote - 1)) / 100);
    if(!modCalled) currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNote) + detuneInHertz;
    setFrequency(currentFreq >= 0 ? currentFreq : 0);
}


void OscData::setModulator(VirtualOsc* modOsc, int modNum) {
    modCalled[modNum] = true;
    jassert(modNum < modulators);
    modulatorOsc[modNum] = modOsc;
}

void OscData::updateModulator() {
    currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNote) + detuneInHertz + modValue;
    setFrequency(currentFreq >= 0 ? currentFreq : 0);
}

void OscData::removeModulator(VirtualOsc* modOsc) {
    for (int i=0; i < modulators; i++) {
        if (modulatorOsc[i] == modOsc) {
            modOsc->setParams(0, 0, 0);
            modulatorOsc[i] = modOsc;
        }
    }
}

//void OscData::setAsMod(bool status) {thisIsModulator = status;}
void OscData::setParams(float lfoRate, float lfoInt, int lfoWaveType) {}
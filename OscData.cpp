/*
  ==============================================================================

    oscData.cpp
    Created: 2 Feb 2022 3:15:58pm
    Author:  ellio

  ==============================================================================
*/

#include "OscData.h"


void OscData::setWaveType(const int waveType) {

    switch ((int)waveType)
    {
    case 0:
        initialise([](float x) {return std::sin(x); });
        break;
    case 1:
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;
    case 2:
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
        break;
    default:
        jassertfalse; //error
        break;
    }
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
    //if (modCalled) modulatorOsc->prepare(spec);
    prepare(spec);
}

void OscData::processBlock(juce::dsp::AudioBlock<float>& block) {
    process(juce::dsp::ProcessContextReplacing<float>(block));
    if (modCalled) modulatorOsc->processBlock(block);
    
}

void OscData::setFreq(const int midiNoteNumber, const int detuneValue, const int courseTuneValue) {
    midiNote = midiNoteNumber + courseTuneValue;
    //detuneValue == 0 ? detuneInHertz = 0 : detuneInHertz = pow(10, ((1200 / detuneValue * log(2)) + log(juce::MidiMessage::getMidiNoteInHertz(midiNote))));
    detuneInHertz = detuneValue * ((juce::MidiMessage::getMidiNoteInHertz(midiNote) - juce::MidiMessage::getMidiNoteInHertz(midiNote - 1)) / 100);
    currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNote) + detuneInHertz;
    //if (modCalled)currentFreq += modulatorOsc->mod;
    setFrequency(currentFreq >= 0 ? currentFreq : 0);
}


void OscData::setModulator(LFOData* modOsc) {
    modCalled = true;
    modulatorOsc = modOsc;
}

void OscData::updateModulator() {
    currentFreq = juce::MidiMessage::getMidiNoteInHertz(midiNote) + detuneInHertz;
    if (modCalled)currentFreq += modulatorOsc->mod;
    setFrequency(currentFreq >= 0 ? currentFreq : 0);
}
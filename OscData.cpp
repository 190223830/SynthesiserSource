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
    for (int i = 0; i < modulators; i++) if (modCalled[i]) modulatorOsc[i]->prepare(spec);
    prepare(spec);
}

float OscData::processBlock(juce::dsp::AudioBlock<float>& block) {
    float temp = 0.0f;
    for (int i = 0; i < modulators; i++) if (modCalled[i]) temp += modulatorOsc[i]->processBlock(block);
    modValue = temp;
    process(juce::dsp::ProcessContextReplacing<float>(block));
    
    return 0;
}

void OscData::setFreq(const int midiNoteNumber, const int detuneValue, const int courseTuneValue) {
    midiNote = midiNoteNumber + courseTuneValue;
    //detuneValue == 0 ? detuneInHertz = 0 : detuneInHertz = pow(10, ((1200 / detuneValue * log(2)) + log(juce::MidiMessage::getMidiNoteInHertz(midiNote))));
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

void OscData::setParams(float lfoRate, float lfoInt, int lfoWaveType) {}
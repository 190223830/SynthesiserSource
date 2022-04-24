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
    
    prepare(spec);
    //modOneOsc.prepare(spec);
}

void OscData::processBlock(juce::dsp::AudioBlock<float>& block) {
    /*for (int channel = 0; channel < block.getNumChannels(); channel++) {
        for (int sample = 0; sample < block.getNumSamples(); sample++) {
            modulator = modulatorOsc.processSample(block.getSample(channel, sample))*modulatorInt;
        }
    }*/
    if(called) modulator = modulatorOsc->mod;
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setFreq(const int midiNoteNumber, const int detuneValue, const int courseTuneValue, float modOne) {
    midiNote = midiNoteNumber + courseTuneValue;
    //detuneValue == 0 ? detuneInHertz = 0 : detuneInHertz = pow(10, ((1200 / detuneValue * log(2)) + log(juce::MidiMessage::getMidiNoteInHertz(midiNote))));
    detuneInHertz = detuneValue * ((juce::MidiMessage::getMidiNoteInHertz(midiNote) - juce::MidiMessage::getMidiNoteInHertz(midiNote - 1)) / 100);
    auto currentFreq(juce::MidiMessage::getMidiNoteInHertz(midiNote) + detuneInHertz + modulator);
    setFrequency(currentFreq >= 0 ? currentFreq : 0);
    
}

//void OscData:: setModParams(const float freq, const float intensity, const int waveType) {

    //switch (waveType)
    //{
    //case 0:
    //    modOneOsc.initialise([](float x) {return std::sin(x); });
    //    break;
    //case 1:
    //    modOneOsc.initialise([](float x) {return x / juce::MathConstants<float>::pi; });
    //    break;
    //case 2:
    //    modOneOsc.initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
    //    break;
    //default:
    //    jassertfalse; //error
    //    break;
    //}

    //modOneOsc.setFrequency(freq);
    //modOneInt = intensity;
    //auto currentFreq(juce::MidiMessage::getMidiNoteInHertz(midiNote) + detuneInHertz + modOne);
    //setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);
//}

void OscData::setModulator(LFOData* modOsc) {
    called = true;
    modulatorOsc = modOsc;
}
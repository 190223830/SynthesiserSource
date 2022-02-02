/*
  ==============================================================================

    oscData.cpp
    Created: 2 Feb 2022 3:15:58pm
    Author:  ellio

  ==============================================================================
*/

#include "oscData.h"

void OscData::setWaveType(const int waveType) {
    //juce::dsp::Oscillator<float> osc;
    //juce::dsp::Oscillator<float> oscSin{ [](float x) {return std::sin(x); } };                          //sine wave
    //juce::dsp::Oscillator<float> oscSaw{ [](float x) {return x / juce::MathConstants<float>::pi; } };   //saw wave
    //juce::dsp::Oscillator<float> oscSqu{ [](float x) {return x < 0.0f ? -1.0f : 1.0f; } };              //square wave

    switch (waveType)
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
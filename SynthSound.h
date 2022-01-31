/*
  ==============================================================================

    SynthSound.h
    Created: 31 Jan 2022 5:41:03am
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};
/*
  ==============================================================================

    Matrix.cpp
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Matrix.h"

JUCE_IMPLEMENT_SINGLETON(Matrix)

void Matrix::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.setFont (10.0f);

    for (int i = 0; i < destinations; i++) {
        for (int j = 0; j < modulators; j++) {
            addAndMakeVisible(buttons[i][j]);
            buttons[i][j].setBounds(60 + (i * 40), 60 + (j * 40), 30, 30);
            buttons[i][j].onClick = [this, i, j]() {toggleValue(i, j);};
        }
    }

    juce::String labelsTop[destinations] = { "OSC 1", "OSC 2", "OSC 3", "OSC 4", "CUTOFF"};
    juce::String labelsSide[modulators] = { "OSC 1", "OSC 2", "OSC 3", "OSC 4", "LFO1", "LFO2"};
    for (int i = 0; i < destinations; i++) {
        g.drawText(labelsTop[i], 60 + (i * 40), 20, 70, 40, juce::Justification::left, false);
    }
    for (int i = 0; i < modulators; i++) {
        g.drawText(labelsSide[i], 10, 60 + (i * 40), 50, 30, juce::Justification::centred, false);
    }
}

void Matrix::resized(){}

void Matrix::toggleValue(int destination, int modulator) {
    jassert(modulator <= modulators && destination <= destinations);
    data[destination][modulator] = !getValue(destination, modulator);
}

bool Matrix::getValue(int destination, int modulator) {
    jassert(modulator <= modulators && destination <= destinations);
    return data[destination][modulator];
}

/*
  ==============================================================================

    FilterVisualiser.cpp
    Created: 22 Apr 2022 2:50:04pm
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterVisualiser.h"

//==============================================================================
FilterVisualiser::FilterVisualiser()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FilterVisualiser::~FilterVisualiser()
{
}

void FilterVisualiser::paint (juce::Graphics& g)
{
    float cutoffPoint = (cutoff / 20000) * getWidth() / 2;
    g.setColour(juce::Colours::darkturquoise);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    juce::Path filterResponse;
    filterResponse.startNewSubPath(0.0f, getHeight() / 2);
    filterResponse.lineTo(cutoffPoint, getHeight()/2);
    filterResponse.closeSubPath();
    g.strokePath(filterResponse, juce::PathStrokeType(5.0f));

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("FilterVisualiser", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void FilterVisualiser::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterVisualiser::update(int filterType, int cutoffFreq, int resonance) {
    type = filterType;
    cutoff = cutoffFreq;
    res = resonance;
}

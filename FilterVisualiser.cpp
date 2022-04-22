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
FilterVisualiser::FilterVisualiser() : AudioVisualiserComponent(0)
{
    //setColours(juce::Colours::black, juce::Colours::black);
};


FilterVisualiser::~FilterVisualiser()
{
}

void FilterVisualiser::paint (juce::Graphics& g)
{
    //g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::darkturquoise);
    g.strokePath(filterResponse, juce::PathStrokeType(2.0f));
    //g.fillAll(juce::Colours::black);
}

void FilterVisualiser::resized()
{

}

void FilterVisualiser::update(int filterType, float cutoffFreq, float resonance) {
        float startingPoint;
        cutoffPoint = (cutoffFreq / 20000) * (getWidth());
        switch (filterType) {
        case 0:
            startingPoint = 0.0f;
            break;
        case 1:
            startingPoint = cutoffPoint;
            break;
        case 2:
            startingPoint = getWidth();
            break;
        default:
            jassertfalse;
            break;
        }
        filterResponse.clear();
        filterResponse.startNewSubPath(startingPoint, getHeight() / 2);
        filterResponse.lineTo(cutoffPoint-50, (getHeight() / 2));
        filterResponse.lineTo(cutoffPoint, (getHeight() / 2)+resonance*10);
        filterResponse.closeSubPath();
}

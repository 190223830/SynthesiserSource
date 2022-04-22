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

    filterResponse.clear();

    filterResponse.startNewSubPath(juce::Point<float>(startingX, startingY));
    filterResponse.lineTo(cutoffPoint);
    filterResponse.lineTo(peakPoint);
    filterResponse.lineTo(endPoint);
    g.strokePath(filterResponse, juce::PathStrokeType(2.0f));
    filterResponse.closeSubPath();
    g.setColour(juce::Colours::black);
    
    //g.fillAll(juce::Colours::black);
}

void FilterVisualiser::resized()
{

}

void FilterVisualiser::update(int filterType, float cutoffFreq, float resonance) {
    startingY = getHeight() / 2;
    cutoffPoint = juce::Point<float>((cutoffFreq / 20000) * getWidth()-20, startingY);
    peakPoint = juce::Point<float>(cutoffPoint.getX()+20*((-filterType)+1), (startingY) - (resonance / 10) * startingY);
    endPoint;
    switch (filterType) {
        case 0:
            startingX = 0.0f;
            endPoint = juce::Point<float>(peakPoint.getX() + 40, getHeight());
            break;
        case 1:
            startingX = cutoffPoint.getX()-40;
            startingY = getHeight();
            cutoffPoint = peakPoint;
            endPoint = juce::Point<float>(peakPoint.getX() + 40, getHeight());
            
            break;
        case 2:
            startingX = getWidth();
            endPoint = juce::Point<float>(peakPoint.getX() - 40, getHeight());
            break;
        default:
            jassertfalse;
            break;
    }
    
}

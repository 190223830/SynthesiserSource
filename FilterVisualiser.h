/*
  ==============================================================================

    FilterVisualiser.h
    Created: 22 Apr 2022 2:50:04pm
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterVisualiser  : public juce::AudioVisualiserComponent//, juce::Timer
{
public:
    FilterVisualiser();
    ~FilterVisualiser() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void update(int filterType, float cutoffFreq, float resonance);

    /*void FilterVisualiser::setRepaintRate(int frequencyInHz)
    {
        startTimerHz(frequencyInHz);
    }

    void FilterVisualiser::timerCallback()
    {
        repaint();
    }*/

    

private:

    juce::Path filterResponse;
    float startingX, startingY;
    juce::Point<float> cutoffPoint, peakPoint, endPoint;
    //float cutoffPoint, startingPoint; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterVisualiser)
};

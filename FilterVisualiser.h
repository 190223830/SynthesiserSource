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
class FilterVisualiser  : public juce::Component
{
public:
    FilterVisualiser();
    ~FilterVisualiser() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void update(int filterType, int cutoffFreq, int resonance);

private:
    int type{ 0 }, cutoff{ 0 }, res{ 0 };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterVisualiser)
};

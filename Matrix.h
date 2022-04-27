/*
  ==============================================================================

    Matrix.h
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Matrix : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void resized() override;

    void toggleValue(int modulator, int destination);
    bool getValue(int modulator, int destination);

    JUCE_DECLARE_SINGLETON(Matrix, true)

private:
    static constexpr auto modulators = 6;
    static constexpr auto destinations = 5;
    static Matrix* instance;
    bool data[destinations][modulators];
    juce::ToggleButton buttons[destinations][modulators];

    Matrix() = default;
    ~Matrix() override {}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Matrix)
};



/*   osc1  osc2   osc3    osc4    filter
osc1
osc2
osc3
osc4
lfo1
lfo2                                    */

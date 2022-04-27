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
    /// <summary>
    /// Re-skins the component.
    /// </summary>
    void paint(juce::Graphics& g) override;

    /// <summary>
    /// How the component will be laid out on screen.
    /// </summary>
    void resized() override;

    /// <summary>
    /// Sets the value of a point in the matrix so other components can check where to send modulation.
    /// </summary>
    /// <param name="modulator">Modulation input</param>
    /// <param name="destination">Modulation output</param>
    void toggleValue(int modulator, int destination);

    /// <summary>
    /// Gets the value of a given point in the matrix
    /// </summary>
    /// <param name="modulator">Modulation input</param>
    /// <param name="destination">Modulation output</param>
    /// <returns>Value of matrix point</returns>
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

/*
  ==============================================================================

    FilterVisualiser.h
    Author:  ellio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterVisualiser  : public juce::AudioVisualiserComponent//, juce::Timer
{
public:
    FilterVisualiser();
    ~FilterVisualiser() override;

    /// <summary>
    /// Re-skins the component.
    /// </summary>
    void paint (juce::Graphics&) override;

    /// <summary>
    /// How the component will be laid out on screen.
    /// </summary>
    void resized() override;

    /// <summary>
    /// Polls the component to show updated information.
    /// </summary>
    /// <param name="filterType">Filter Type</param>
    /// <param name="cutoffFreq">Filter Cutoff</param>
    /// <param name="resonance">Filter Resonance</param>
    void update(int filterType, float cutoffFreq, float resonance);

private:
    juce::Path filterResponse;
    float startingX, startingY;
    juce::Point<float> cutoffPoint, peakPoint, endPoint;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterVisualiser)
};

class FilterVisualiserSpectrogram : public juce::AudioAppComponent, juce::Timer
{
public:
    static constexpr auto fftOrder = 11;                // 2^(fftOrder) points of measurement
    static constexpr auto fftSize = 1 << fftOrder;      //left bit shift - converts fftOrder to binary

    FilterVisualiserSpectrogram();
    ~FilterVisualiserSpectrogram() override;

    /// <summary>
    /// Re-skins the component.
    /// </summary>
    void paint(juce::Graphics&) override;

    /// <summary>
    /// Sets the 'resolution' of the component, and how often it should pass to the output.
    /// </summary>
    /// <param name="sampleRate"> How often does the parameter register a change </param>
    /// <param name="samplesPerBlockExpected"> How often should the component output </param>
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /// <summary>
    /// Runs upon destruction of component.
    /// </summary>
    void releaseResources() override;

    /// <summary>
    /// Retreives the next audio block before passing it into the visualiser
    /// </summary>
    /// <param name="bufferToFill"> Audio buffer </param>
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    /// <summary>
    /// Pushes each sample into the visualiser from memory.
    /// </summary>
    /// <param name="sample">Sample to push</param>
    void pushNextSampleIntoInbound(float sample) noexcept;

    /// <summary>
    /// Repaints component to update on the interface.
    /// </summary>
    void timerCallback() override;

    /// <summary>
    /// Draws each frame of the visualiser.
    /// </summary>
    void drawFrame(juce::Graphics& g);

    /// <summary>
    /// Draws the frame onto the interface.
    /// </summary>
    void drawNextFrame();

private:
    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;         
    float inbound[fftSize];         // incoming samples
    float results[2 * fftSize];     // calculation 
    int graphPoints = 512;
    float graph[512];
    int index = 0;
    bool nextFFTBlockReady = false; // renderNextBlock trigger


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterVisualiserSpectrogram)
};

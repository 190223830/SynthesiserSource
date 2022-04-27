/*
  ==============================================================================

    FilterVisualiser.h
    Created: 22 Apr 2022 2:50:04pm
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
    void paint (juce::Graphics&) override;
    void resized() override;
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
    void paint(juce::Graphics&) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void pushNextSampleIntoInbound(float sample) noexcept;
    void timerCallback() override;
    void drawFrame(juce::Graphics& g);
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

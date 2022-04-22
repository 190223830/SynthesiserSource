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
}

void FilterVisualiser::resized()
{

}

void FilterVisualiser::update(int filterType, float cutoffFreq, float resonance) {
    startingY = getHeight() / 2;
    cutoffPoint = juce::Point<float>((cutoffFreq / 20000) * getWidth()-20, startingY);
    peakPoint = juce::Point<float>(cutoffPoint.getX()+40*((-filterType)+1), (startingY) - (resonance / 10) * startingY);
    endPoint;
    switch (filterType) {
        case 0:
            startingX = 0.0f;
            endPoint = juce::Point<float>(peakPoint.getX() + 80, getHeight());
            break;
        case 1:
            startingX = cutoffPoint.getX()-80;
            startingY = getHeight();
            cutoffPoint = peakPoint;
            endPoint = juce::Point<float>(peakPoint.getX() + 80, getHeight());
            
            break;
        case 2:
            startingX = getWidth();
            endPoint = juce::Point<float>(peakPoint.getX() - 80, getHeight());
            break;
        default:
            jassertfalse;
            break;
    }
    

}

FilterVisualiserSpectrogram::FilterVisualiserSpectrogram() : forwardFFT(fftOrder),
                                                             window(fftSize, juce::dsp::WindowingFunction<float>::hann)
{
    setAudioChannels(2, 0);
    startTimerHz(60);
}

FilterVisualiserSpectrogram::~FilterVisualiserSpectrogram() { shutdownAudio(); }



void FilterVisualiserSpectrogram::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (bufferToFill.buffer->getNumChannels() > 0)
    {
        auto* channelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);

        for (auto i = 0; i < bufferToFill.numSamples; ++i)
            pushNextSampleIntoInbound(channelData[i]);
    }
}

void FilterVisualiserSpectrogram::pushNextSampleIntoInbound(float sample) noexcept
{
    if (index == fftSize)
    {
        if (!nextFFTBlockReady)
        {
            //std::fill(results.begin(), results.end(), 0.0f);
            //std::copy(inbound.begin(), inbound.end(), results.begin());
            juce::zeromem(results, sizeof(results));
            memcpy(results, inbound, sizeof(inbound));
            nextFFTBlockReady = true;
        }
        index = 0;
    }
    inbound[(size_t)index++] = sample;
}

void FilterVisualiserSpectrogram::drawNextFrame()
{
    // first apply a windowing function to our data
    window.multiplyWithWindowingTable(results, fftSize);       // [1]

    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform(results);  // [2]

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    for (int i = 0; i < graphPoints; ++i)                         // [3]
    {
        auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - (float)i / (float)graphPoints) * 0.2f);
        auto resultsIndex = juce::jlimit(0, fftSize / 2, (int)(skewedProportionX * (float)fftSize * 0.5f));
        auto level = juce::jmap(juce::jlimit(mindB, maxdB, juce::Decibels::gainToDecibels(results[resultsIndex])
            - juce::Decibels::gainToDecibels((float)fftSize)),
            mindB, maxdB, 0.0f, 1.0f);

        graph[i] = level;                                   // [4]
    }
}

void FilterVisualiserSpectrogram::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    g.setOpacity(1.0f);
    g.setColour(juce::Colours::white);
    drawFrame(g);
}

void FilterVisualiserSpectrogram::timerCallback()
{
    if (nextFFTBlockReady)
    {
        drawNextFrame();
        nextFFTBlockReady = false;
        repaint();
    }
}

void FilterVisualiserSpectrogram::drawFrame(juce::Graphics& g)
{
    for (int i = 1; i < graphPoints; ++i)
    {
        auto width = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();

        g.drawLine({ (float)juce::jmap(i - 1, 0, graphPoints - 1, 0, width),
                              juce::jmap(graph[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
                      (float)juce::jmap(i,     0, graphPoints - 1, 0, width),
                              juce::jmap(graph[i],     0.0f, 1.0f, (float)height, 0.0f) });
    }
}

void FilterVisualiserSpectrogram::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}

void FilterVisualiserSpectrogram::releaseResources() {}
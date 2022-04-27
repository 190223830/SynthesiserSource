/*
  ==============================================================================

    FilterVisualiser.cpp
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterVisualiser.h"

FilterVisualiser::FilterVisualiser() : AudioVisualiserComponent(0) {}
FilterVisualiser::~FilterVisualiser() {}

void FilterVisualiser::paint (juce::Graphics& g)
{
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

void FilterVisualiser::resized() {}

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
                                                             window(fftSize, juce::dsp::WindowingFunction<float>::blackman)
{ startTimerHz(60); }

FilterVisualiserSpectrogram::~FilterVisualiserSpectrogram() { shutdownAudio(); }



void FilterVisualiserSpectrogram::getNextAudioBlock(const juce::AudioSourceChannelInfo& emptyBuffer)
{
    if (emptyBuffer.buffer->getNumChannels() > 0)
    {
        auto* channelData = emptyBuffer.buffer->getReadPointer(0, emptyBuffer.startSample);
        for (int i = 0; i < emptyBuffer.numSamples; i++) pushNextSampleIntoInbound(channelData[i]);
    }
}

void FilterVisualiserSpectrogram::pushNextSampleIntoInbound(float sample) noexcept
{
    if (index == fftSize)
    {
        if (!nextFFTBlockReady)
        {
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
    window.multiplyWithWindowingTable(results, fftSize);
    forwardFFT.performFrequencyOnlyForwardTransform(results);

    for (int i = 0; i < graphPoints; i++)
    {
        auto logSkew = 1.0f - std::exp(std::log(1.0f - (float)i / (float)graphPoints) * 0.2f);
        auto resultsIndex = juce::jlimit(0, fftSize / 2, (int)(logSkew * (float)fftSize * 0.5f));
        auto level = juce::jmap(juce::jlimit(-100.0f, 0.0f, juce::Decibels::gainToDecibels(results[resultsIndex])
            - juce::Decibels::gainToDecibels((float)fftSize)),
            -100.0f, 0.0f, 0.0f, 1.0f);

        graph[i] = level;
    }
}

void FilterVisualiserSpectrogram::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::darkturquoise);
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
    for (int i = 1; i < graphPoints; i++)
    {

        g.drawLine({ (float)juce::jmap(i - 1, 0, graphPoints - 1, 0, getWidth()),
                            juce::jmap(graph[i - 1], 0.0f, 1.0f, (float)getHeight(), 0.0f),

                     (float)juce::jmap(i,     0, graphPoints - 1, 0, getWidth()),
                            juce::jmap(graph[i],     0.0f, 1.0f, (float)getHeight(), 0.0f) });
    }
}

void FilterVisualiserSpectrogram::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}
void FilterVisualiserSpectrogram::releaseResources() {}
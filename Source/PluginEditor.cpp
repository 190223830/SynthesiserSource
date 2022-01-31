#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthOneAudioProcessorEditor::SynthOneAudioProcessorEditor (SynthOneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //set the editor's size
    setSize (400, 300);
}

SynthOneAudioProcessorEditor::~SynthOneAudioProcessorEditor()
{

}

void SynthOneAudioProcessorEditor::paint (juce::Graphics& g)
{
    // fill the background with a solid colour
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("SynthOne", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthOneAudioProcessorEditor::resized()
{
    // lay out the positions of any subcomponents
}

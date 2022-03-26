#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthOneAudioProcessorEditor::SynthOneAudioProcessorEditor (SynthOneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    adsr(audioProcessor.valueTreeState, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    osc(audioProcessor.valueTreeState, "WAVE", "MODONEFREQ", "MODONEINT", "MODONEWAVE"),
    filter(audioProcessor.valueTreeState, "FILTERTYPE"),
    egAdsr(audioProcessor.valueTreeState, "EGATTACK", "EGDECAY", "EGSUSTAIN", "EGRELEASE"),
    lfo1(audioProcessor.valueTreeState, "LFO1RATE", "LFO1INT", "LFO1WAVE"),
    lfo2(audioProcessor.valueTreeState, "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    gainSlider("Gain", "GAIN", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    //set the editor's size
    setSize (800, 900);

    addAndMakeVisible(gainSlider);


    //make adsr and osc visible
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(egAdsr);
    addAndMakeVisible(lfo1);
    addAndMakeVisible(lfo2);

}

SynthOneAudioProcessorEditor::~SynthOneAudioProcessorEditor()
{
}

void SynthOneAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void SynthOneAudioProcessorEditor::resized()
{
    adsr.setBounds(getWidth() / 2 + 80, 20, getWidth() / 2 - 80, (getHeight() / 8) + 80);
    osc.setBounds(0, 0, getWidth() / 2 - 120, getHeight());
    gainSlider.setBounds(osc.getRight(), 20, 90, getHeight()/8 + 80);
    filter.setBounds(getWidth() / 2, getHeight() / 2, getWidth() / 2, getHeight() / 4 + 80);
    egAdsr.setBounds(getWidth() /2 + 80, filter.getY()+getHeight()/8 +40, getWidth() /2 -80, (getHeight() / 8 + 80));
    lfo1.setBounds(getWidth()/2, 700, getWidth()/2, 100);
    lfo2.setBounds(getWidth() / 2, 800, getWidth() / 2, 100);
}

#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthOneAudioProcessorEditor::SynthOneAudioProcessorEditor (SynthOneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    adsr0(audioProcessor.valueTreeState, "ATTACK0", "DECAY0", "SUSTAIN0", "RELEASE0"),
    adsr1(audioProcessor.valueTreeState, "ATTACK1", "DECAY1", "SUSTAIN1", "RELEASE1"),
    adsr2(audioProcessor.valueTreeState, "ATTACK2", "DECAY2", "SUSTAIN2", "RELEASE2"),
    adsr3(audioProcessor.valueTreeState, "ATTACK3", "DECAY3", "SUSTAIN3", "RELEASE3"),
    osc0(audioProcessor.valueTreeState, "WAVE0", "LFO1RATE", "LFO1INT", "LFO1WAVE"),
    osc1(audioProcessor.valueTreeState, "WAVE1", "LFO1RATE", "LFO1INT", "LFO1WAVE"),
    osc2(audioProcessor.valueTreeState, "WAVE2", "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    osc3(audioProcessor.valueTreeState, "WAVE3", "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    filter(audioProcessor.valueTreeState, "FILTERTYPE"),
    egAdsr(audioProcessor.valueTreeState, "EGATTACK", "EGDECAY", "EGSUSTAIN", "EGRELEASE"),
    lfo1(audioProcessor.valueTreeState, "LFO1RATE", "LFO1INT", "LFO1WAVE"),
    lfo2(audioProcessor.valueTreeState, "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    gainSlider0("Gain", "GAIN0", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    gainSlider1("Gain", "GAIN1", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    gainSlider2("Gain", "GAIN2", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    gainSlider3("Gain", "GAIN3", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    detuneSlider0("Detune", "DETUNE0", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    detuneSlider1("Detune", "DETUNE1", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    detuneSlider2("Detune", "DETUNE2", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    detuneSlider3("Detune", "DETUNE3", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    voiceSlider("Voices", "VOICES", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    unisonSlider("Poly/Unison", "UNISON", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag)
{
    //set the editor's size
    setSize (800, 900);

    addAndMakeVisible(gainSlider0);
    addAndMakeVisible(gainSlider1);
    addAndMakeVisible(gainSlider2);
    addAndMakeVisible(gainSlider3);
    addAndMakeVisible(detuneSlider0);
    addAndMakeVisible(detuneSlider1);
    addAndMakeVisible(detuneSlider2);
    addAndMakeVisible(detuneSlider3);

    //addAndMakeVisible(voiceSlider);
    addAndMakeVisible(unisonSlider);


    //make adsr and osc visible
    addAndMakeVisible(adsr0);
    addAndMakeVisible(adsr1);
    addAndMakeVisible(adsr2);
    addAndMakeVisible(adsr3);
    addAndMakeVisible(osc0);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
    addAndMakeVisible(filter);
    addAndMakeVisible(egAdsr);
    addAndMakeVisible(lfo1);
    addAndMakeVisible(lfo2);

    //setVisualiser();
    addAndMakeVisible(audioProcessor.visualiser);
    

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
    adsr0.setBounds(getWidth() / 2 + 80, 300, getWidth() / 2 - 80, 100);
    adsr1.setBounds(getWidth() / 2 + 80, 0, getWidth() / 2 - 80, 100);
    adsr2.setBounds(getWidth() / 2 + 80, 100, getWidth() / 2 - 80, 100);
    adsr3.setBounds(getWidth() / 2 + 80, 200, getWidth() / 2 - 80, 100);
    osc0.setBounds(0, 300, getWidth() / 2 - 120, 100);
    osc1.setBounds(0, 0, getWidth() / 2 - 120, 100);
    osc2.setBounds(0, 100, getWidth() / 2 - 120, 100);
    osc3.setBounds(0, 200, getWidth() / 2 - 120, 100);
    gainSlider0.setBounds(osc0.getRight(), 300, 90, 100);
    gainSlider1.setBounds(osc1.getRight(), 0, 90, 100);
    gainSlider2.setBounds(osc2.getRight(), 100, 90, 100);
    gainSlider3.setBounds(osc3.getRight(), 200, 90, 100);
    detuneSlider0.setBounds(gainSlider0.getRight(), 300, 90, 100);
    detuneSlider1.setBounds(gainSlider1.getRight(), 0, 90, 100);
    detuneSlider2.setBounds(gainSlider2.getRight(), 100, 90, 100);
    detuneSlider3.setBounds(gainSlider3.getRight(), 200, 90, 100);

    filter.setBounds(getWidth() / 2, getHeight() / 2, getWidth() / 2, getHeight() / 4 + 80);
    egAdsr.setBounds(getWidth() /2 + 80, filter.getY()+getHeight()/8 +40, getWidth() /2 -80, (getHeight() / 8 + 80));
    lfo1.setBounds(getWidth()/2, 700, getWidth()/2, 100);
    lfo2.setBounds(getWidth() / 2, 800, getWidth() / 2, 100);
    audioProcessor.visualiser.setBounds(25, getHeight() - 100, getWidth() / 2 -50, 80);
    //voiceSlider.setBounds(unisonSlider.getRight(), getHeight() - 200, 90, 100);
    unisonSlider.setBounds(25, getHeight() - 200, 90, 100);
    
}
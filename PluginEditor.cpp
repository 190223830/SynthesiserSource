#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthOneAudioProcessorEditor::SynthOneAudioProcessorEditor(SynthOneAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
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
    courseTuneSlider0("Course Tune", "COURSETUNE0", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    courseTuneSlider1("Course Tune", "COURSETUNE1", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    courseTuneSlider2("Course Tune", "COURSETUNE2", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    courseTuneSlider3("Course Tune", "COURSETUNE3", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    panSlider0("Pan", "PAN0", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    panSlider1("Pan", "PAN1", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    panSlider2("Pan", "PAN2", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    panSlider3("Pan", "PAN3", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    voiceSlider("Voices", "VOICES", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),        //removed
    unisonSlider("Poly/Unison", "UNISON", audioProcessor.valueTreeState, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag),
    keyboard(p.keyboardState, juce::MidiKeyboardComponent::Orientation::horizontalKeyboard)
{
    //set the editor's size
    setSize(800, 875);

    addAndMakeVisible(gainSlider0);
    addAndMakeVisible(gainSlider1);
    addAndMakeVisible(gainSlider2);
    addAndMakeVisible(gainSlider3);
    addAndMakeVisible(detuneSlider0);
    addAndMakeVisible(detuneSlider1);
    addAndMakeVisible(detuneSlider2);
    addAndMakeVisible(detuneSlider3);
    addAndMakeVisible(courseTuneSlider0);
    addAndMakeVisible(courseTuneSlider1);
    addAndMakeVisible(courseTuneSlider2);
    addAndMakeVisible(courseTuneSlider3);
    addAndMakeVisible(panSlider0);
    addAndMakeVisible(panSlider1);
    addAndMakeVisible(panSlider2);
    addAndMakeVisible(panSlider3);
    addAndMakeVisible(voiceSlider);
    addAndMakeVisible(unisonSlider);
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
    addAndMakeVisible(audioProcessor.visualiser);
    addAndMakeVisible(keyboard);


}

SynthOneAudioProcessorEditor::~SynthOneAudioProcessorEditor()
{
}

void SynthOneAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));


}

void SynthOneAudioProcessorEditor::resized()
{
    gainSlider0.setBounds(adsr0.getRight(), 320, 75, 100);
    gainSlider1.setBounds(adsr1.getRight(), 20, 75, 100);
    gainSlider2.setBounds(adsr2.getRight(), 120, 75, 100);
    gainSlider3.setBounds(adsr3.getRight(), 220, 75, 100);
    osc0.setBounds(gainSlider0.getRight(), 320, 200, 100);
    osc1.setBounds(gainSlider1.getRight(), 20, 200, 100);
    osc2.setBounds(gainSlider2.getRight(), 120, 200, 100);
    osc3.setBounds(gainSlider3.getRight(), 220, 200, 100);
    adsr0.setBounds(osc0.getRight(), 320, 300, 100);
    adsr1.setBounds(osc1.getRight(), 20, 300, 100);
    adsr2.setBounds(osc2.getRight(), 120, 300, 100);
    adsr3.setBounds(osc3.getRight(), 220, 300, 100);
    detuneSlider0.setBounds(adsr0.getRight(), 320, 75, 100);
    detuneSlider1.setBounds(adsr1.getRight(), 20, 75, 100);
    detuneSlider2.setBounds(adsr2.getRight(), 120, 75, 100);
    detuneSlider3.setBounds(adsr3.getRight(), 220, 75, 100);
    courseTuneSlider0.setBounds(detuneSlider0.getRight(), 320, 75, 100);
    courseTuneSlider1.setBounds(detuneSlider1.getRight(), 20, 75, 100);
    courseTuneSlider2.setBounds(detuneSlider2.getRight(), 120, 75, 100);
    courseTuneSlider3.setBounds(detuneSlider3.getRight(), 220, 75, 100);
    panSlider0.setBounds(courseTuneSlider0.getRight(), 320, 75, 100);
    panSlider1.setBounds(courseTuneSlider1.getRight(), 20, 75, 100);
    panSlider2.setBounds(courseTuneSlider2.getRight(), 120, 75, 100);
    panSlider3.setBounds(courseTuneSlider3.getRight(), 220, 75, 100);

    filter.setBounds(425, 420, getWidth() / 2, 200);
    egAdsr.setBounds(500, 520, getWidth() /2 -75, 100);
    lfo1.setBounds(425, 620, getWidth()/2-150, 100);
    lfo2.setBounds(425, 720, getWidth()/2-150, 100);
    audioProcessor.visualiser.setBounds(25, 720, getWidth() / 2 - 50, 80);
    voiceSlider.setBounds(getWidth()-75, 620, 75, 100);
    unisonSlider.setBounds(getWidth()-75, 720, 75, 100);
    keyboard.setBounds(0, getHeight() - 50, getWidth(), 50);

};
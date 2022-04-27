#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthOneAudioProcessorEditor::SynthOneAudioProcessorEditor(SynthOneAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    adsr0(audioProcessor.valueTreeState, "ATTACK0", "DECAY0", "SUSTAIN0", "RELEASE0"),
    adsr1(audioProcessor.valueTreeState, "ATTACK1", "DECAY1", "SUSTAIN1", "RELEASE1"),
    adsr2(audioProcessor.valueTreeState, "ATTACK2", "DECAY2", "SUSTAIN2", "RELEASE2"),
    adsr3(audioProcessor.valueTreeState, "ATTACK3", "DECAY3", "SUSTAIN3", "RELEASE3"),
    osc0(audioProcessor.valueTreeState, "WAVE0", "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    osc1(audioProcessor.valueTreeState, "WAVE1", "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    osc2(audioProcessor.valueTreeState, "WAVE2", "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    osc3(audioProcessor.valueTreeState, "WAVE3", "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    filter(audioProcessor.valueTreeState, "FILTERTYPE"),
    egAdsr(audioProcessor.valueTreeState, "EGATTACK", "EGDECAY", "EGSUSTAIN", "EGRELEASE"),
    lfo1(audioProcessor.valueTreeState, "LFO1RATE", "LFO1INT", "LFO1WAVE"),
    lfo2(audioProcessor.valueTreeState, "LFO2RATE", "LFO2INT", "LFO2WAVE"),
    gainSlider0("Gain", "GAIN0", audioProcessor.valueTreeState ),
    gainSlider1("Gain", "GAIN1", audioProcessor.valueTreeState ),
    gainSlider2("Gain", "GAIN2", audioProcessor.valueTreeState ),
    gainSlider3("Gain", "GAIN3", audioProcessor.valueTreeState ),
    detuneSlider0("Detune", "DETUNE0", audioProcessor.valueTreeState ),
    detuneSlider1("Detune", "DETUNE1", audioProcessor.valueTreeState ),
    detuneSlider2("Detune", "DETUNE2", audioProcessor.valueTreeState ),
    detuneSlider3("Detune", "DETUNE3", audioProcessor.valueTreeState ),
    courseTuneSlider0("Course Tune", "COURSETUNE0", audioProcessor.valueTreeState ),
    courseTuneSlider1("Course Tune", "COURSETUNE1", audioProcessor.valueTreeState ),
    courseTuneSlider2("Course Tune", "COURSETUNE2", audioProcessor.valueTreeState ),
    courseTuneSlider3("Course Tune", "COURSETUNE3", audioProcessor.valueTreeState ),
    panSlider0("Pan", "PAN0", audioProcessor.valueTreeState ),
    panSlider1("Pan", "PAN1", audioProcessor.valueTreeState ),
    panSlider2("Pan", "PAN2", audioProcessor.valueTreeState ),
    panSlider3("Pan", "PAN3", audioProcessor.valueTreeState ),
    voiceSlider("Voices", "VOICES", audioProcessor.valueTreeState ),
    unisonSlider("Poly/Unison", "UNISON", audioProcessor.valueTreeState ),
    keyboard(p.keyboardState, juce::MidiKeyboardComponent::Orientation::horizontalKeyboard)
{
    //set the editor's size
    setSize(640, 700);

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
    addAndMakeVisible(audioProcessor.filterVisualiser);
    addAndMakeVisible(audioProcessor.filterVisualiserSpectrogram);
    addAndMakeVisible(keyboard);
    addAndMakeVisible(matrix);


}

SynthOneAudioProcessorEditor::~SynthOneAudioProcessorEditor(){}

void SynthOneAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.setFont(10.0f);
    g.setGradientFill(
        juce::ColourGradient(
            juce::Colour(0xFF263238),
            0,
            0,
            juce::Colours::black,
            0,
            650,
            false
        ));
    g.fillAll();
}

void SynthOneAudioProcessorEditor::resized()
{
    gainSlider0.setBounds(0, 210, 70, 75);
    gainSlider1.setBounds(0, 0, 70, 75);
    gainSlider2.setBounds(0, 70, 70, 75);
    gainSlider3.setBounds(0, 140, 70, 75);
    osc0.setBounds(gainSlider0.getRight(), 210, 70, 75);
    osc1.setBounds(gainSlider1.getRight(), 0, 70, 75);
    osc2.setBounds(gainSlider2.getRight(), 70, 70, 75);
    osc3.setBounds(gainSlider3.getRight(), 140, 70, 75);
    adsr0.setBounds(osc0.getRight(), 210, 280, 75);
    adsr1.setBounds(osc1.getRight(), 0, 280, 75);
    adsr2.setBounds(osc2.getRight(), 70, 280, 75);
    adsr3.setBounds(osc3.getRight(), 140, 280, 75);
    detuneSlider0.setBounds(adsr0.getRight(), 210, 70, 75);
    detuneSlider1.setBounds(adsr1.getRight(), 0, 70, 75);
    detuneSlider2.setBounds(adsr2.getRight(), 70, 70, 75);
    detuneSlider3.setBounds(adsr3.getRight(), 140, 70, 75);
    courseTuneSlider0.setBounds(detuneSlider0.getRight(), 210, 70, 75);
    courseTuneSlider1.setBounds(detuneSlider1.getRight(), 0, 70, 75);
    courseTuneSlider2.setBounds(detuneSlider2.getRight(), 70, 70, 75);
    courseTuneSlider3.setBounds(detuneSlider3.getRight(), 140, 70, 75);
    panSlider0.setBounds(courseTuneSlider0.getRight(), 210, 70, 75);
    panSlider1.setBounds(courseTuneSlider1.getRight(), 0, 70, 75);
    panSlider2.setBounds(courseTuneSlider2.getRight(), 70, 70, 75);
    panSlider3.setBounds(courseTuneSlider3.getRight(), 140, 70, 75);

    filter.setBounds(280, 280, 210, 150);
    egAdsr.setBounds(350, 350, 280, 75);
    lfo1.setBounds(280, 420, 210, 75);
    lfo2.setBounds(280, 490, 210, 75);
    audioProcessor.visualiser.setBounds(0, 570, getWidth() / 2, 80);
    audioProcessor.filterVisualiserSpectrogram.setBounds(getWidth() / 2, 570, getWidth() / 2, 80);
    audioProcessor.filterVisualiser.setBounds(getWidth() / 2, 570, getWidth() / 2, 80);
    voiceSlider.setBounds(560, 420, 70, 75);
    unisonSlider.setBounds(560, 490, 70, 75);
    keyboard.setBounds(0, 650, getWidth(), 50);
    matrix->setBounds(0, 280, 280, 290);

};
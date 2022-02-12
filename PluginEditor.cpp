#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthOneAudioProcessorEditor::SynthOneAudioProcessorEditor (SynthOneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    adsr(audioProcessor.valueTreeState, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    osc(audioProcessor.valueTreeState, "WAVE", "MODONEFREQ", "MODONEINT", "MODONEWAVE"),
    filter(audioProcessor.valueTreeState, "FILTERTYPE"),
    modEG(audioProcessor.valueTreeState, "EGATTACK", "EGDECAY", "EGSUSTAIN", "EGRELEASE")
{
    //set the editor's size
    setSize (800, 400);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, "GAIN", gainSlider);
    //waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.valueTreeState, "WAVE", waveSelect);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    addAndMakeVisible(gainSlider);
    gainLabel.setFont(15.0f);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);

    //make adsr and osc visible
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(modEG);

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
    //g.drawFittedText ("SynthOne", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthOneAudioProcessorEditor::resized()
{
    // lay out the positions of any subcomponents
    
    //set adsr bounds
    adsr.setBounds(getWidth()/2, 20, getWidth()/2, (getHeight()/8)+80);
    osc.setBounds(100, 0, getWidth()/2-120, getHeight());

    gainSlider.setBounds(10, 10, 50, getHeight()-40);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() + gainSlider.getHeight()-5, gainSlider.getWidth(), 20);

    filter.setBounds(getWidth()/2, getHeight()/2+60, getWidth()/2, getHeight()/2);

    modEG.setBounds(getWidth() / 2, 20+ (getHeight() / 8) + 50, getWidth() / 2, (getHeight() / 8) + 80);
}

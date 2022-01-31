#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthOneAudioProcessorEditor::SynthOneAudioProcessorEditor (SynthOneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //set the editor's size
    setSize (800, 400);

    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, "RELEASE", releaseSlider);

    //gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTreeState, "GAIN", gainSlider);;
    waveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.valueTreeState, "WAVE", waveSelect);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);     //you could probably make a method for this to keep the code dry
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    //gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
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
    const auto adsrSection = getLocalBounds();//.reduced(10);
    const auto adsrPadding = 10;
    const auto adsrSliderWidth = adsrSection.getWidth()/4-adsrPadding;
    const auto adsrSliderHeight = adsrSection.getWidth()/4-adsrPadding;
    const auto adsrSliderX = 0;
    const auto adsrSliderY = adsrSection.getHeight() / 2 - (adsrSliderHeight / 2);

    attackSlider.setBounds(adsrSliderX, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    decaySlider.setBounds(attackSlider.getRight()+adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + adsrPadding, adsrSliderY, adsrSliderWidth, adsrSliderHeight);
}

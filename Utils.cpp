/*
  ==============================================================================

    Utils.cpp
    Author:  ellio

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Utils.h"



using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using SliderStyle = juce::Slider::SliderStyle;

GenericSlider::GenericSlider(juce::String labelName, juce::String parameter, juce::AudioProcessorValueTreeState& valueTreeState, SliderStyle style)
{
    juce::LookAndFeel::setDefaultLookAndFeel(&skin);
    slider.setSliderStyle(style);
    slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, textBoxWidth, textBoxHeight);
    addAndMakeVisible(slider);

    label.setFont(fontSize);
    label.setText(labelName, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    attachment = std::make_unique<SliderAttachment>(valueTreeState, parameter, slider);
}
GenericSlider::~GenericSlider() { juce::LookAndFeel::setDefaultLookAndFeel(nullptr); }


void GenericSlider::resized()
{
    slider.setBounds(0, 0, sliderWidth, sliderHeight);
    label.setBounds(0, sliderHeight-10, sliderWidth, labelHeight);   
}


Utils::Utils(){}
Utils::~Utils(){}
void Utils::paint(juce::Graphics& g){}
void Utils::resized(){}



void SynthesiserPlusAddons::noteOn(const int midiChannel,
    const int midiNoteNumber,
    const float velocity)
{
    for (auto* sound : sounds)
    {
        if (sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
        {
            // If hitting a note that's still ringing, stop it first (it could be
            // still playing because of the sustain or sostenuto pedal).
            for (auto* voice : voices)
                if (voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel(midiChannel))
                    stopVoice(voice, 1.0f, true);
            for (int i = 0; i < unisonNo; i++) {
                startVoice(findFreeVoice(sound, midiChannel, midiNoteNumber, true),
                    sound, midiChannel, midiNoteNumber, velocity);
            }
        }
    }
}

void SynthesiserPlusAddons::setUnisonNo(const int unisonId)
{
    unisonNo = unisonId;
}

void SynthesiserPlusAddons::removeVoices(const int voicesToRemove)
{

    for(int i=0; i<voicesToRemove; i++)
    {
        int indexToRemove = -1;
        for (auto* voice : juce::Synthesiser::voices)
        {
            if (!voice->isVoiceActive())
            {
                indexToRemove = voices.indexOf(voice);
                break;
            }
        }

        if (indexToRemove > -1) voices.remove(indexToRemove);
        else { voices.remove(0); }
    }
};

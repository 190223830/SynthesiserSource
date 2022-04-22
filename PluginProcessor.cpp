#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Utils.h"
#include <iostream>

SynthOneAudioProcessor::SynthOneAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), valueTreeState (*this, nullptr, "Params", createParams())
#endif
{
    synth.addSound(new SynthSound());
    for (int i = 0; i < userSetVoices; i++) synth.addVoice(new SynthVoice());
}

SynthOneAudioProcessor::~SynthOneAudioProcessor()
{
}

const juce::String SynthOneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthOneAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthOneAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthOneAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthOneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthOneAudioProcessor::getNumPrograms()
{
    return 1;   // this should be at least 1, even if you're not really implementing programs.    
}

int SynthOneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthOneAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthOneAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthOneAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void SynthOneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // pre-playback initialisation

    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        };
    };
    

    //filter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());

}

void SynthOneAudioProcessor::releaseResources()
{
    // When playback stops
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthOneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // check if the layout is supported.

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthOneAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    int counter = 0;
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto& unisonNo = *valueTreeState.getRawParameterValue("UNISON");
    synth.setUnisonNo(unisonNo);

    userSetVoices = *valueTreeState.getRawParameterValue("VOICES");
    if (userSetVoices*unisonNo != synth.getNumVoices())
    {
        int voiceD = userSetVoices - synth.getNumVoices();
        if (voiceD > 0) {
            for (int i = 0; i < voiceD; i++) synth.addVoice(new SynthVoice);
            prepareToPlay(synth.getSampleRate(), buffer.getNumSamples());
        }
        else {
            synth.removeVoices(-voiceD);
        }
    }

    for (int i = 0; i < synth.getNumVoices(); i++) { 
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            juce::String oscNumStr = std::to_string((i + 1) % 4);
            int waveType = *valueTreeState.getRawParameterValue("WAVE" + oscNumStr);
            float attack = *valueTreeState.getRawParameterValue("ATTACK" + oscNumStr);
            float decay = *valueTreeState.getRawParameterValue("DECAY" + oscNumStr);
            float sustain = *valueTreeState.getRawParameterValue("SUSTAIN" + oscNumStr);
            float release = *valueTreeState.getRawParameterValue("RELEASE" + oscNumStr);
            float gain = *valueTreeState.getRawParameterValue("GAIN" + oscNumStr);
            int detune = *valueTreeState.getRawParameterValue("DETUNE" + oscNumStr);
            int courseTune = *valueTreeState.getRawParameterValue("COURSETUNE" + oscNumStr);
            float pan = *valueTreeState.getRawParameterValue("PAN" + oscNumStr);

            voice->getOsc().setWaveType(waveType);
            voice->update(attack, decay, sustain, release);
            voice->updateGain(gain);
            voice->updateDetune(detune, courseTune);
            voice->setPanValue(pan);
            
            

            

            //LFO/FM MODS
            //auto& modOneFreq = *valueTreeState.getRawParameterValue("MODONEFREQ");
            //auto& modOneInt = *valueTreeState.getRawParameterValue("MODONEINT");
            //auto& modOneWaveType = *valueTreeState.getRawParameterValue("MODONEWAVE");
            //voice->getOsc().setModParams(modOneFreq, modOneInt, modOneWaveType);

            auto& lfo1Rate = *valueTreeState.getRawParameterValue("LFO1RATE");
            auto& lfo1Int = *valueTreeState.getRawParameterValue("LFO1INT");
            auto& lfo1WaveType = *valueTreeState.getRawParameterValue("LFO1WAVE");
            //voice->getLFO().setParams(lfo1Rate, lfo1Int, lfo1WaveType);
            voice->getOsc().setModParams(lfo1Rate, lfo1Int, lfo1WaveType);

            auto& lfo2Rate = *valueTreeState.getRawParameterValue("LFO2RATE");
            auto& lfo2Int = *valueTreeState.getRawParameterValue("LFO2INT");
            auto& lfo2WaveType = *valueTreeState.getRawParameterValue("LFO2WAVE");
            //voice->getLFO().setParams(lfo2Rate, lfo2Int, lfo2WaveType);
            voice->getOsc().setModParams(lfo2Rate, lfo2Int, lfo2WaveType);

            //EG ADSR
            auto& egAttack = *valueTreeState.getRawParameterValue("EGATTACK");
            auto& egDecay = *valueTreeState.getRawParameterValue("EGDECAY");
            auto& egSustain = *valueTreeState.getRawParameterValue("EGSUSTAIN");
            auto& egRelease = *valueTreeState.getRawParameterValue("EGRELEASE");
            voice->updateEGADSR(egAttack, egDecay, egSustain, egRelease);
            

            //FILTER
            auto& filterType = *valueTreeState.getRawParameterValue("FILTERTYPE");
            auto& filterCutoff = *valueTreeState.getRawParameterValue("CUTOFF");
            auto& filterResonance = *valueTreeState.getRawParameterValue("RESONANCE");
            auto& modIntensity = *valueTreeState.getRawParameterValue("EGINT");
            voice->updateFilter(filterType, filterCutoff, filterResonance, modIntensity);        
        };
    };
    
    filterVisualiser.update(*valueTreeState.getRawParameterValue("FILTERTYPE"),
                            *valueTreeState.getRawParameterValue("CUTOFF"),
                            *valueTreeState.getRawParameterValue("RESONANCE"));

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    visualiser.pushBuffer(buffer);
    //filter.prepare(buffer);*/
}

bool SynthOneAudioProcessor::hasEditor() const
{
    return true;    // creates GUI
}

juce::AudioProcessorEditor* SynthOneAudioProcessor::createEditor()
{
    return new SynthOneAudioProcessorEditor (*this);
}

void SynthOneAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // use this method to store your parameters in the memory block
}

void SynthOneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // use this method to restore your parameters from this memory block
}

// create new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthOneAudioProcessor();
}

//Value tree
juce::AudioProcessorValueTreeState::ParameterLayout SynthOneAudioProcessor::createParams() {        // create parameters for user input
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    for (int i = 0; i < 4; i++) {
        juce::String str = std::to_string(i);
        params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK" + str, "Attack", juce::NormalisableRange<float>{0.001f, 5.00f, 0.01f}, 0.050f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY" + str, "Decay", juce::NormalisableRange<float>{0.003f, 5.00f, 0.01f}, 0.50f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN" + str, "Sustain", juce::NormalisableRange<float>{0.004f, 1.00f, 0.01f}, 1.00f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE" + str, "Release", juce::NormalisableRange<float>{0.004f, 5.00f, 0.01f}, 0.00f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN" + str, "Gain", juce::NormalisableRange<float>{0.001f, 1.00f, 0.01f}, 0.50f));
        params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVE" + str, "Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
        params.push_back(std::make_unique<juce::AudioParameterInt>("DETUNE" + str, "Detune", -100, 100, 0));
        params.push_back(std::make_unique<juce::AudioParameterInt>("COURSETUNE" + str, "Course Tune", -100, 100, 0));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("PAN" + str, "Pan", -1.0f, 1.0f, 0.0f));
    }

    //params.push_back(std::make_unique<juce::AudioParameterFloat>("MODONEFREQ", "Modulator 1 Frequency", juce::NormalisableRange<float>{0.0f, 1000.0f, 0.1f, 0.2f}, 0.0f));
    //params.push_back(std::make_unique<juce::AudioParameterFloat>("MODONEINT", "Modulator 1 Intensity", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.3f}, 0.0f));
    //params.push_back(std::make_unique<juce::AudioParameterChoice>("MODONEWAVE", "Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    //params.push_back(std::make_unique<juce::AudioParameterFloat>("MODTWOFREQ", "Modulator 2 Frequency", juce::NormalisableRange<float>{0.0f, 1000.0f, 0.1f, 0.2f}, 0.0f));
    //params.push_back(std::make_unique<juce::AudioParameterFloat>("MODTWOINT", "Modulator 2 Intensity", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.3f}, 0.0f));
    //params.push_back(std::make_unique<juce::AudioParameterChoice>("MODTWOWAVE", "Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    //

    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "LPF", "BPF", "HPF" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CUTOFF", "Filter Cutoff Frequency", juce::NormalisableRange<float>{20.f, 20000.f, 1.f, 0.3f}, 10000.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RESONANCE", "Filter Resonance", juce::NormalisableRange<float>{0.1f, 10.f, 0.f, 0.2f}, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGATTACK", "EG Attack", juce::NormalisableRange<float>{0.001f, 5.00f, 0.01f}, 0.050f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGDECAY", "EG Decay", juce::NormalisableRange<float>{0.003f, 5.00f, 0.01f}, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGSUSTAIN", "EG Sustain", juce::NormalisableRange<float>{0.004f, 1.00f, 0.01f}, 1.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGRELEASE", "EG Release", juce::NormalisableRange<float>{0.004f, 5.00f, 0.01f}, 0.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGINT", "EG Intensity", juce::NormalisableRange<float>{-1.0f, 1000.0f, 0.1f, 0.3f}, 0.00f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFO1RATE", "LFO Rate", juce::NormalisableRange<float>{0.0f, 20.0f, 0.1f, 0.2f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFO1INT", "LFO Intensity", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.3f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("LFO1WAVE", "LFO Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFO2RATE", "LFO Rate", juce::NormalisableRange<float>{0.0f, 20.0f, 0.1f, 0.2f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFO2INT", "LFO Intensity", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.3f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("LFO2WAVE", "LFO Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    params.push_back(std::make_unique<juce::AudioParameterInt>("UNISON", "Poly/Unison", 1, 4, 1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("VOICES", "Voices", 1, 20, 8));

    return { params.begin(), params.end() };
}
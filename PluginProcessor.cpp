#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    for (int i = 0; i < 5; i++) {           //make it create a new voice whenever a new midi note is pressed
        synth.addVoice(new SynthVoice());
    }
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
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            //Osc controls
            auto& waveType = *valueTreeState.getRawParameterValue("WAVE");
            voice->getOsc().setWaveType(waveType);

            //ADSR
            auto& attack = *valueTreeState.getRawParameterValue("ATTACK");
            auto& decay = *valueTreeState.getRawParameterValue("DECAY");
            auto& sustain = *valueTreeState.getRawParameterValue("SUSTAIN");
            auto& release = *valueTreeState.getRawParameterValue("RELEASE");
            voice->update(attack.load(), decay.load(), sustain.load(), release.load()); //.load() is because its an atomic float, uses a lot more power than a normal float (not actually necessary but good for reference)

            //GAIN
            auto& gain = *valueTreeState.getRawParameterValue("GAIN");
            voice->updateGain(gain.load());

            //LFO/FM MODS
            auto& modOneFreq = *valueTreeState.getRawParameterValue("MODONEFREQ");
            auto& modOneInt = *valueTreeState.getRawParameterValue("MODONEINT");
            auto& modOneWaveType = *valueTreeState.getRawParameterValue("MODONEWAVE");
            voice->getOsc().setModParams(modOneFreq, modOneInt, modOneWaveType);

            auto& lfoRate = *valueTreeState.getRawParameterValue("LFORATE");
            auto& lfoInt = *valueTreeState.getRawParameterValue("LFOINT");
            auto& lfoWaveType = *valueTreeState.getRawParameterValue("LFOWAVE");
            voice->getOsc().setModParams(lfoRate, lfoInt, lfoWaveType);

            //EG ADSR
            auto& egAttack = *valueTreeState.getRawParameterValue("EGATTACK");
            auto& egDecay = *valueTreeState.getRawParameterValue("EGDECAY");
            auto& egSustain = *valueTreeState.getRawParameterValue("EGSUSTAIN");
            auto& egRelease = *valueTreeState.getRawParameterValue("EGRELEASE");
            voice->updateEGADSR(egAttack.load(), egDecay.load(), egSustain.load(), egRelease.load()); //this may need to go last
            

            //FILTER
            auto& filterType = *valueTreeState.getRawParameterValue("FILTERTYPE");
            auto& filterCutoff = *valueTreeState.getRawParameterValue("CUTOFF");
            auto& filterResonance = *valueTreeState.getRawParameterValue("RESONANCE");
            auto& modIntensity = *valueTreeState.getRawParameterValue("EGINT"); //this should probably be done within egADSR
            voice->updateFilter(filterType.load(), filterCutoff.load(), filterResonance.load(), modIntensity.load());
        };
    };

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    /*filter.updateParams(filterType, filterCutoff, filterResonance);
    filter.prepare(buffer);*/
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
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{0.001f, 5.00f, 0.01f}, 0.050f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{0.003f, 5.00f, 0.01f}, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{0.004f, 1.00f, 0.01f}, 1.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{0.004f, 5.00f, 0.01f}, 0.00f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", juce::NormalisableRange<float>{0.001f, 1.00f, 0.01f}, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVE", "Wave Type", juce::StringArray{ "Sine", "Saw", "Square"}, 0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODONEFREQ", "Modulator 1 Frequency", juce::NormalisableRange<float>{0.0f, 1000.0f, 0.1f, 0.2f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODONEINT", "Modulator 1 Intensity", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.3f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("MODONEWAVE", "Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "LPF", "BPF", "HPF" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CUTOFF", "Filter Cutoff Frequency", juce::NormalisableRange<float>{20.0f, 20000.0f, 0.0f, 0.3f}, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RESONANCE", "Filter Resonance", juce::NormalisableRange<float>{0.1f, 10.0f, 0.0f, 0.2f}, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGATTACK", "EG Attack", juce::NormalisableRange<float>{0.001f, 5.00f, 0.01f}, 0.050f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGDECAY", "EG Decay", juce::NormalisableRange<float>{0.003f, 5.00f, 0.01f}, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGSUSTAIN", "EG Sustain", juce::NormalisableRange<float>{0.004f, 1.00f, 0.01f}, 1.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGRELEASE", "EG Release", juce::NormalisableRange<float>{0.004f, 5.00f, 0.01f}, 0.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGINT", "EG Intensity", juce::NormalisableRange<float>{-1.0f, 10.0f, 0.1f, 0.3f}, 0.00f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFORATE", "LFO Rate", juce::NormalisableRange<float>{0.0f, 1000.0f, 0.1f, 0.2f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFOINT", "LFO Intensity", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.3f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("LFOWAVE", "LFO Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    return { params.begin(), params.end() };
}

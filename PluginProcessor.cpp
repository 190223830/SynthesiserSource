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
    synth.addVoice(new SynthVoice());
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

            //AMP EG
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

            //MOD EG
            auto& EGAttack = *valueTreeState.getRawParameterValue("EGATTACK");
            auto& EGDecay = *valueTreeState.getRawParameterValue("EGDECAY");
            auto& EGSustain = *valueTreeState.getRawParameterValue("EGSUSTAIN");
            auto& EGRelease = *valueTreeState.getRawParameterValue("EGRELEASE");

            //FILTER
            auto& filterType = *valueTreeState.getRawParameterValue("FILTERTYPE");
            auto& filterCutoff = *valueTreeState.getRawParameterValue("CUTOFF");
            auto& filterResonance = *valueTreeState.getRawParameterValue("RESONANCE");

            voice->updateModEG(EGAttack, EGDecay, EGSustain, EGRelease);
            voice->updateFilter(filterType.load(), filterCutoff.load(), filterResonance.load());
            
        };
    };

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

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
    //AMP EG
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{0.001f, 5.00f, 0.01f}, 0.050f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{0.003f, 5.00f, 0.01f}, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{0.004f, 1.00f, 0.01f}, 1.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{0.004f, 5.00f, 0.01f}, 0.00f));

    //GAIN
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", juce::NormalisableRange<float>{0.001f, 1.00f, 0.01f}, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVE", "Wave Type", juce::StringArray{ "Sine", "Saw", "Square"}, 0));

    //FM MOD ONE
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODONEFREQ", "Modulator 1 Frequency", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.2f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODONEINT", "Modulator 1 Intensity", juce::NormalisableRange<float>{0.0f, 1000.0f, 1.0f, 0.3f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("MODONEWAVE", "Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    //FILTER
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "LPF", "BPF", "HPF" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CUTOFF", "Filter Cutoff Frequency", juce::NormalisableRange<float>{20.0f, 20000.0f, 0.0f, 0.3f}, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RESONANCE", "Filter Resonance", juce::NormalisableRange<float>{0.1f, 10.0f, 0.0f, 0.2f}, 0.0f));
    
    //MOD EG
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGATTACK", "Attack", juce::NormalisableRange<float>{0.001f, 5.00f, 0.01f}, 0.050f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGDECAY", "Decay", juce::NormalisableRange<float>{0.003f, 5.00f, 0.01f}, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGSUSTAIN", "Sustain", juce::NormalisableRange<float>{0.004f, 1.00f, 0.01f}, 1.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EGRELEASE", "Release", juce::NormalisableRange<float>{0.004f, 5.00f, 0.01f}, 0.00f));
    
    return { params.begin(), params.end() };
}

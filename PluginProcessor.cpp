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
        if (auto voice = dynamic_cast<juce::SynthesiserVoice*>(synth.getVoice(i))) {
            //Osc controls
            //ADSR
            //LFO

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
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.00f, 1.00f, 0.10f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 0.00f, 1.00f, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.00f, 1.00f, 1.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.00f, 1.00f, 0.00f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.00f, 1.00f, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVE", "Wave type", juce::StringArray{ "Sine", "Saw", "Square"}, 0));

    return { params.begin(), params.end() };
}
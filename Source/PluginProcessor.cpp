/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
COM418AudioProcessor::COM418AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

COM418AudioProcessor::~COM418AudioProcessor()
{
}

//==============================================================================
const juce::String COM418AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool COM418AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool COM418AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool COM418AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double COM418AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int COM418AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int COM418AudioProcessor::getCurrentProgram()
{
    return 0;
}

void COM418AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String COM418AudioProcessor::getProgramName (int index)
{
    return {};
}

void COM418AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void COM418AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void COM418AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool COM418AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void COM418AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool COM418AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* COM418AudioProcessor::createEditor()
{
  //  return new COM418AudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void COM418AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void COM418AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout COM418AudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    
    /* Oscillator section
    Osc waveType => Sine, Saw, Square
    */
    
    juce::StringArray waveTypeChoices = {"Sine", "Saw", "Square"};
    layout.add(std::make_unique<juce::AudioParameterChoice>("WaveType", "WaveType", waveTypeChoices, 0));
    
    /* Amp section parameters
    AmpGain => Gain knob (-10 dB / +10 dB : 1db)
     
    ADSR
    AmpAttack => Attack Slider (0ms / 5s : 1ms)
    AmpDecay => Decay Slider (0ms / 5s : 1ms)
    AmpSustain => Sustain Slider (0 / 10 : 0.5)
    AmpRelease => Release Slider (0 / 5s : 1ms)
    */
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpGain",
                                                          "Gain",
                                                          juce::NormalisableRange<float>(-10.f, 10.f, .5f, 1.f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpAttack",
                                                          "Attack",
                                                          juce::NormalisableRange<float>(0.0f, 5000.f, 1.f, 1.f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpDecay",
                                                          "Decay",
                                                          juce::NormalisableRange<float>(0.0f, 5000.f, 1.f, 1.f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpSustain",
                                                          "Sustain",
                                                          juce::NormalisableRange<float>(0.0f, 10.0f, 0.5f, 1.f),
                                                           10.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpRelease",
                                                          "Release",
                                                          juce::NormalisableRange<float>(0.0f, 5000.f, 1.f, 1.f),
                                                           0.0f));
    
    // filter section parameters
    layout.add(std::make_unique<juce::AudioParameterFloat>("FilterAttack",
                                                          "Attack",
                                                          juce::NormalisableRange<float>(0.0f, 5000.f, 1.f, 1.f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("FilterDecay",
                                                          "Decay",
                                                          juce::NormalisableRange<float>(0.0f, 5000.f, 1.f, 1.f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("FilterSustain",
                                                          "Sustain",
                                                          juce::NormalisableRange<float>(0.0f, 10.0f, 1.f, 1.f),
                                                           10.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("FilterRelease",
                                                          "Release",
                                                          juce::NormalisableRange<float>(0.0f, 5000.f, 1.f, 1.f),
                                                           0.0f));
    
    return layout;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new COM418AudioProcessor();
}

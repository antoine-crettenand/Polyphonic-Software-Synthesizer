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
                       ), apvts(*this, nullptr, "Parameters", createParameterLayout(3)) //NUMBER_OSCILLATORS=3 must be given since NUMBER_OSCILLATORS is not yet instantiated
                        
#endif
{
    //no need call delete for memory, handled
    synth.addSound(new SynthSound());
    for (int i = 0; i < NUMBER_OSCILLATORS; ++i)
    {
        synth.addVoice(new SynthVoice());
    }

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
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for(int i = 0; i < synth.getNumVoices(); i++)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
        
    }
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

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for(int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            //osc controls; adsr; lfo

            std::string voiceName = "Osc" + std::to_string(i+1) + "WaveType";
            auto& oscWaveChoice = *apvts.getRawParameterValue(voiceName);
            
            // Amp ADSR parameters
            AmpSettings ampSettings = getAmpSettings(apvts);
            voice->update(ampSettings.attack, ampSettings.decay, ampSettings.sustain, ampSettings.release);
            voice->getOscillator().setWaveType(oscWaveChoice);
        }
    }

    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool COM418AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* COM418AudioProcessor::createEditor()
{
    return new COM418AudioProcessorEditor (*this);
  //  return new juce::GenericAudioProcessorEditor(*this);
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

juce::AudioProcessorValueTreeState::ParameterLayout COM418AudioProcessor::createParameterLayout(int numberOscillators)
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    
    /* Oscillator section
    Osc waveType => Sine, Saw, Square
    */
    
    juce::StringArray waveTypeChoices = {"Sine", "Saw", "Square"};

    for (int i = 0; i < numberOscillators; ++i)
    {
        layout.add(std::make_unique<juce::AudioParameterChoice>("Osc" + std::to_string(i + 1) + "WaveType", "Osc " + std::to_string(i + 1) + " Wave Type", waveTypeChoices, 0));
        layout.add(std::make_unique<juce::AudioParameterInt>("Freq" + std::to_string(i + 1),
                                                            "Frequency Oscillator" + std::to_string(i + 1),
                                                            -12, 12, 0));
        layout.add(std::make_unique<juce::AudioParameterFloat>("Volume" + std::to_string(i + 1),
                                                            "Volume Oscillator" + std::to_string(i + 1),
                                                            juce::NormalisableRange<float>(-5.f, 5.f, 1.f, 1.f),
                                                            0));
    }

    /* Amp section parameters
    AmpGain => Gain knob (-10 dB / +10 dB : 1db) - not implemented
     
    ADSR
    AmpAttack => Attack Slider (0ms / 5s : 1ms)
    AmpDecay => Decay Slider (0ms / 5s : 1ms)
    AmpSustain => Sustain Slider (0 / 10 : 0.5)
    AmpRelease => Release Slider (0 / 5s : 1ms)
    */
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpGain",
                                                          "Gain",
                                                          juce::NormalisableRange<float>(-10.f, 10.f, .5f, .5f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpAttack",
                                                          "Attack",
                                                          juce::NormalisableRange<float>(0.0f, 5.f, .001f, .5f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpDecay",
                                                          "Decay",
                                                          juce::NormalisableRange<float>(0.0f, 5.f, .001f, 1.f),
                                                           0.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpSustain",
                                                          "Sustain",
                                                          juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f, 1.f),
                                                           10.0f));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>("AmpRelease",
                                                          "Release",
                                                          juce::NormalisableRange<float>(0.0f, 5.f, .001f, .5f),
                                                           0.0f));
    
    /*
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
    */
    return layout;
}

AmpSettings getAmpSettings(juce::AudioProcessorValueTreeState& apvts){
    AmpSettings ampSettings;
    
    ampSettings.gain = apvts.getRawParameterValue("AmpGain")->load();

    ampSettings.attack = apvts.getRawParameterValue("AmpAttack")->load();
    ampSettings.decay = apvts.getRawParameterValue("AmpDecay")->load();
    ampSettings.sustain = apvts.getRawParameterValue("AmpSustain")->load();
    ampSettings.release = apvts.getRawParameterValue("AmpRelease")->load();
    
    return ampSettings;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new COM418AudioProcessor();
}

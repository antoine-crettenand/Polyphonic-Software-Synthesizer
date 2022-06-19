# Polyphonic-Software-Synthesizer
The polyphonic-software synthesizer is a synthesizer in the form of a VST3/AU plugin containing multiple oscillators and differents effects : filters, tremolo, delay, distortion. You can download the plugin by following the instructions in the [dedicated section](#Download). A presentation of the presets you can use is made [afterwards](#Presets).  
The ressources we used to create this synth were mainly the [JUCE documentation](https://juce.com/learn/documentation) and the [AudioProgrammer tutorials](https://www.theaudioprogrammer.com/).
## Project structure
- JuceLibraryCode : all the libraries provided by the JUCE framework
- Source/ : 
  - PluginEditor :
  - PluginProcessor :
  - Synth :
  - SynthVoice : 
  - Data/ :
    - AdsrData
    - CircularBuffer
    - DelayData
    - DistortionData
    - FilterData
    - ModEffectData
    - OscData
    - TimeEffectData
    - Tremolo
  - UI/ : 
    - AdsrComponent
    - DelayComponent
    - DistortionComponent
    - FilterComponent
    - FullOscsComponent
    - ModEffectComponent
    - OscComponent
    - WaveformVisualizerComponent
## Installation 
If you want only to use the already built plugins and not the all JUCE project, please go to the [next section](#Download).

## Download
To only download the VST3 and AU plugins, please click on the following [link](https://download-directory.github.io/?url=https%3A%2F%2Fgithub.com%2Fantoine-crettenand%2FPolyphonic-Software-Synthesizer%2Ftree%2Frelease%2Fplugins). Then make sure to place them in the correct directory w.r.t. your OS :

| Plugin type | MacOSX                              | Windows                            |
|-------------|-------------------------------------|------------------------------------|
| AU          | ~/Library/Audio/Plug-Ins/Components | Not supported                      |
| VST3        | ~/Library/Audio/Plug-Ins/VST3       | C:\Program Files\Common Files\VST3 |

## Synthesizer controls

## Presets
Here you can find a video of some presets we have found :


https://user-images.githubusercontent.com/43465471/174476560-ac63e572-d3ec-4d77-86e5-a3977c7c6fb2.mp4







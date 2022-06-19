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
If you want only to use the already built plugins and not the all JUCE project, please go to the [next section](#Download). To launch the project, please first install [JUCE](https://juce.com/get-juce/download). After that, you will have to have either [XCode](https://apps.apple.com/ch/app/xcode/id497799835?mt=12) for Mac users or [Visual Studio](https://visualstudio.microsoft.com/) for Windows. You can then clone this github repository. To launch the project you will have to execute the COM418.jucer file, a Projucer window will appear. Click then on the Xcode or Visual Code icon on the top of the window. To execute the project so that the plugin runs on your DAW, you will have to select the right version (VST3/AU), make sure to be on release mode and then build the project.  Here is an example for MacOSX with GarageBand. These steps may slightly change with the DAW or the OS you have selectioned.



https://user-images.githubusercontent.com/43465471/174483290-87f09886-37a9-45b9-9cfc-cb6476fd3b62.mp4



It is possible that if you use GarageBand, the plugin does not appear. If it is the case, please execute `killall -9 AudioComponentRegistrar` in your Terminal after having closed Garage



Band.

## Download
To only download the VST3 and AU plugins, please click on the following [link](https://download-directory.github.io/?url=https%3A%2F%2Fgithub.com%2Fantoine-crettenand%2FPolyphonic-Software-Synthesizer%2Ftree%2Frelease%2Fplugins). Then make sure to place them in the correct directory with respect to your OS :

| Plugin type | MacOSX                              | Windows                            |
|-------------|-------------------------------------|------------------------------------|
| AU          | ~/Library/Audio/Plug-Ins/Components | Not supported                      |
| VST3        | ~/Library/Audio/Plug-Ins/VST3       | C:\Program Files\Common Files\VST3 |

You will find two versions of each: the standard one and the light one. The difference between them is that the light version do not contain the Wave visualization, because it could cause for some computers lags.


## Presets
Here you can find a video of some presets that you can use :


https://user-images.githubusercontent.com/43465471/174476560-ac63e572-d3ec-4d77-86e5-a3977c7c6fb2.mp4







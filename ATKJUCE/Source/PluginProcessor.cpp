/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include <cstring>

#include <boost/math/constants/constants.hpp>

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ATKJUCEAudioProcessor::ATKJUCEAudioProcessor()
:
#ifndef JucePlugin_PreferredChannelConfigurations
    AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
inL(nullptr, 1, 0, false), inR(nullptr, 1, 0, false), outL(nullptr, 1, 0, false), outR(nullptr, 1, 0, false)
{
  outL.set_input_port(0, &inL, 0);
  bufferFilterL.set_input_port(0, &inL, 0);
  outR.set_input_port(0, &inR, 0);
  bufferFilterR.set_input_port(0, &inR, 0);
  pipeline.add_filter(&outL);
  pipeline.add_filter(&outR);
  pipeline.add_filter(&bufferFilterL);
  pipeline.add_filter(&bufferFilterR);
}

ATKJUCEAudioProcessor::~ATKJUCEAudioProcessor()
{
}

//==============================================================================
const String ATKJUCEAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ATKJUCEAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ATKJUCEAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double ATKJUCEAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ATKJUCEAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ATKJUCEAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ATKJUCEAudioProcessor::setCurrentProgram (int index)
{
}

const String ATKJUCEAudioProcessor::getProgramName (int index)
{
    return {};
}

void ATKJUCEAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ATKJUCEAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  sampling_rate = std::lround(sampleRate);

	inL.set_input_sampling_rate(sampling_rate);
	inL.set_output_sampling_rate(sampling_rate);
	inR.set_input_sampling_rate(sampling_rate);
	inR.set_output_sampling_rate(sampling_rate);

	outL.set_input_sampling_rate(sampling_rate);
	outL.set_output_sampling_rate(sampling_rate);
  outR.set_input_sampling_rate(sampling_rate);
	outR.set_output_sampling_rate(sampling_rate);
  bufferFilterL.set_input_sampling_rate(sampling_rate);
  bufferFilterL.set_output_sampling_rate(sampling_rate);
  bufferFilterR.set_input_sampling_rate(sampling_rate);
  bufferFilterR.set_output_sampling_rate(sampling_rate);
  
  pipeline.set_input_sampling_rate(sampling_rate);
}

void ATKJUCEAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ATKJUCEAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void ATKJUCEAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
  auto nb_samples = buffer.getNumSamples();

  inL.set_pointer(buffer.getReadPointer(0), nb_samples);
  inR.set_pointer(buffer.getReadPointer(1), nb_samples);
  outL.set_pointer(buffer.getWritePointer(0), nb_samples);
  outR.set_pointer(buffer.getWritePointer(1), nb_samples);
 
  pipeline.process(nb_samples);
}

//==============================================================================
bool ATKJUCEAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ATKJUCEAudioProcessor::createEditor()
{
    return new ATKJUCEAudioProcessorEditor (*this);
}

//==============================================================================
void ATKJUCEAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ATKJUCEAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

int ATKJUCEAudioProcessor::get_sampling_rate() const
{
  return sampling_rate;
}

std::size_t ATKJUCEAudioProcessor::get_nb_channels() const
{
  return 2;
}

const std::vector<double>& ATKJUCEAudioProcessor::get_last_slice(std::size_t index, bool& process)
{
  if(index == 0)
  {
    process = process_slice(bufferFilterL, windowedDataL);
    return windowedDataL;
  }
  else
  {
    process = process_slice(bufferFilterR, windowedDataR);
    return windowedDataR;
  }
}

bool ATKJUCEAudioProcessor::process_slice(ATK::OutCircularPointerFilter<float>& filter, std::vector<double>& windowedData)
{
  bool process = false;
  
  const auto& data = filter.get_last_slice(process);
  if(process)
  {
    if(window.size() != data.size())
    {
      build_window(data.size());
    }
    for(std::size_t i = 0; i < data.size(); ++i)
    {
      windowedData[i] = window[i] * data[i];
    }
  }
  return process;
}

void ATKJUCEAudioProcessor::build_window(std::size_t size)
{
  window.resize(size, 0);
  windowedDataL.resize(size);
  windowedDataR.resize(size);
  for(size_t i = 0; i < size; ++i)
  {
    window[i] = .5 * (1 - std::cos(2 * boost::math::constants::pi<float>() * i / (size / 2 - 1)));
  }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new ATKJUCEAudioProcessor();
}

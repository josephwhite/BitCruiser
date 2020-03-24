/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
static Array<float> getSimpleNoise(int numSamples) {
    Random r = Random::getSystemRandom();
    Array<float> noise;
    for (int s = 0; s < numSamples; s++) {
        noise.add((r.nextFloat() - .5) * 2);
    }
    return noise;
}

JuceSynthFrameworkAudioProcessor::JuceSynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )
    , tree(*this, nullptr, "PARAMETERS",
        { std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
            std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(1.0f, 2000.0f), 1.0f),
            std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 1.0f), 0.8f),
            std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
            std::make_unique<AudioParameterFloat>("wavetype", "WaveType", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("wavetype2", "WaveType2", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("wavetype3", "WaveType3", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("wavetype4", "WaveType4", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("filterType", "FilterType", NormalisableRange<float>(0.0f, 2.0f), 0.0f),
            std::make_unique<AudioParameterFloat>("filterCutoff", "FilterCutoff", NormalisableRange<float>(20.0f, 10000.0f), 400.0f),
            std::make_unique<AudioParameterFloat>("filterRes", "FilterRes", NormalisableRange<float>(1.0f, 5.0f), 1.0f),
            std::make_unique<AudioParameterFloat>("blend", "Osc2Blend", NormalisableRange<float>(0.0f, 1.0f), 0.6f),
            std::make_unique<AudioParameterFloat>("blend2", "Osc3Blend", NormalisableRange<float>(0.0f, 1.0f), 0.6f),
            std::make_unique<AudioParameterFloat>("blend3", "Osc4Blend", NormalisableRange<float>(0.0f, 1.0f), 0.6f),
            std::make_unique<AudioParameterFloat>("crushDown", "CrushDown", NormalisableRange<float>(1.0f, 50.0f), 1.0f),
            std::make_unique<AudioParameterFloat>("crushRes", "CrushRes", NormalisableRange<float>(1.0f, 32.0f), 32.0f),
            std::make_unique<AudioParameterFloat>("crushTog", "CrushTog", NormalisableRange<float>(1.0f, 2.0f), 1.0f),
            std::make_unique<AudioParameterFloat>("mastergain", "MasterGain", NormalisableRange<float>(0.0f, 1.0f), 0.7f),
            std::make_unique<AudioParameterFloat>("pbup", "PBup", NormalisableRange<float>(1.0f, 12.0f), 2.0f),
            std::make_unique<AudioParameterFloat>("pbdown", "PBdown", NormalisableRange<float>(1.0f, 12.0f), 2.0f),
        })
#endif
{
    mySynth.clearVoices();
    
    for (int i = 0; i < 5; i++) {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
	keyCount = 61;
}

JuceSynthFrameworkAudioProcessor::~JuceSynthFrameworkAudioProcessor() {
}

const String JuceSynthFrameworkAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool JuceSynthFrameworkAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceSynthFrameworkAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int JuceSynthFrameworkAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs, so this should be at least 1, even if you're not really implementing programs.
}

int JuceSynthFrameworkAudioProcessor::getCurrentProgram() {
    return 0;
}

void JuceSynthFrameworkAudioProcessor::setCurrentProgram (int index) {
}

const String JuceSynthFrameworkAudioProcessor::getProgramName (int index) {
    return {};
}

void JuceSynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName) {
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    stateVariableFilter.reset();
    stateVariableFilter.prepare(spec);
    updateFilter();
}

void JuceSynthFrameworkAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported. In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void JuceSynthFrameworkAudioProcessor::updateFilter() {
    int menuChoice = *tree.getRawParameterValue("filterType");
    int freq = *tree.getRawParameterValue("filterCutoff");
    int res = *tree.getRawParameterValue("filterRes");
    
    if (menuChoice == 0) {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
    if (menuChoice == 1) {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
}

void JuceSynthFrameworkAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

	//change color of keyboard on press
	MidiMessage msg;
	int ignore;
	for (MidiBuffer::Iterator it(midiMessages); it.getNextEvent(msg, ignore);) {
		if (msg.isNoteOn()) {
			keyboardState.noteOn(msg.getChannel(), msg.getNoteNumber(), msg.getVelocity() / 127.0f);
		}
		else if (msg.isNoteOff()) {
			keyboardState.noteOff(msg.getChannel(), msg.getNoteNumber(), msg.getVelocity() / 127.0f);
		}
	}

    //get the voice and get the params needed to make the voice
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        //if myVoice sucessfully casts as a SynthVoice*, get the voice and set the params
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {
            myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"),
                                       tree.getRawParameterValue("decay"),
                                       tree.getRawParameterValue("sustain"),
                                       tree.getRawParameterValue("release"));
            
            myVoice->getOscType(tree.getRawParameterValue("wavetype"));
            myVoice->getOsc2Type(tree.getRawParameterValue("wavetype2"));
            myVoice->getOsc3Type(tree.getRawParameterValue("wavetype3"));
            myVoice->getOsc4Type(tree.getRawParameterValue("wavetype4"));
            
            myVoice->getFilterParams(tree.getRawParameterValue("filterType"),
                                     tree.getRawParameterValue("filterCutoff"),
                                     tree.getRawParameterValue("filterRes"));
            
            myVoice->getWillsParams(tree.getRawParameterValue("mastergain"),
                                    tree.getRawParameterValue("blend"),
                                    tree.getRawParameterValue("blend2"),
                                    tree.getRawParameterValue("blend3"),
                                    tree.getRawParameterValue("pbup"),
                                    tree.getRawParameterValue("pbdown"));
        }
    }
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    bool isCrushOn = *(tree.getRawParameterValue("crushTog")) > 1.2f;

    if (isCrushOn) {
        int numSamples = buffer.getNumSamples();
        float bitDepthF = *(tree.getRawParameterValue("crushRes"));
        int bitDepth = (int)round(bitDepthF);
        float rateDivideF =  *(tree.getRawParameterValue("crushDown"));
        int rateDivide = (int)round(rateDivideF);
        float noiseAmt = -120 + 120 * (rateDivide / 100); // dB

        cout << "Bit Depth: " << bitDepth << endl;
        cout << "Rate Divide: " << rateDivide << endl;

        if (noiseBuffer.getNumSamples() != numSamples) {
            noiseBuffer.setSize(2, numSamples, false, true, true); // clears
            currentOutputBuffer.setSize(2, numSamples, false, true, true); // clears
        }

        currentOutputBuffer.copyFrom(0, 0, buffer.getReadPointer(0), numSamples);
        if (buffer.getNumChannels() > 1) {
            currentOutputBuffer.copyFrom(1, 0, buffer.getReadPointer(1), numSamples);
        }

        // Building Noise
        {
            noiseBuffer.clear();
            Array<float> noise = getSimpleNoise(numSamples);
            // range bound
            noiseAmt = jlimit<float>(0, 1, noiseAmt);
            FloatVectorOperations::multiply(noise.getRawDataPointer(), noiseAmt, numSamples);

            // Add the noise ...
            FloatVectorOperations::add(noiseBuffer.getWritePointer(0), noise.getRawDataPointer(), numSamples); // MONO
            FloatVectorOperations::add(noiseBuffer.getWritePointer(1), noise.getRawDataPointer(), numSamples); // STEREO

        }
        // Add noise to the incoming audio
        currentOutputBuffer.addFrom(0, 0, noiseBuffer.getReadPointer(0), numSamples);
        currentOutputBuffer.addFrom(1, 0, noiseBuffer.getReadPointer(1), numSamples);

        // Resample as needed
        for (int chan = 0; chan < currentOutputBuffer.getNumChannels(); chan++) {
            float* data = currentOutputBuffer.getWritePointer(chan);
            for (int i = 0; i < numSamples; i++) {
                // Reduce bit depth
                float totalQLevels = powf(2, bitDepth);
                float val = data[i];
                float remainder = fmodf(val, 1/totalQLevels);
                // Quantize
                data[i] = val - remainder;
                if (rateDivide > 1) {
                    if (i % rateDivide != 0) {
                        data[i] = data[i - i%rateDivide];
                    }
                }
            }
        }
        // Copy to the actual output buffer
        buffer.copyFrom(0, 0, currentOutputBuffer, 0, 0, numSamples);
        buffer.copyFrom(1, 0, currentOutputBuffer, 1, 0, numSamples);
    }

    updateFilter();
    dsp::AudioBlock<float> block(buffer);
    stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool JuceSynthFrameworkAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceSynthFrameworkAudioProcessor::createEditor() {
	return new JuceSynthFrameworkAudioProcessorEditor(*this, keyboardState);
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes as intermediaries to make it easy to save and load complex data.
}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block, whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new JuceSynthFrameworkAudioProcessor();
}
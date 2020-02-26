/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Oscillator2.h"
#include "Oscillator3.h"
#include "Oscillator4.h"
#include "MidiKeyboardComp.h"
#include "Envelope.h"
#include "Filter.h"
#include "Crusher.h"
#include "Frontgui.h"
#include "SimpReverb.h"

//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessorEditor  : public AudioProcessorEditor {
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&, MidiKeyboardState&);
    ~JuceSynthFrameworkAudioProcessorEditor();
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    Oscillator oscGui;
    Oscillator2 osc2Gui;
    Oscillator3 osc3Gui;
    Oscillator4 osc4Gui;
    Filter filterGui;
    Crusher crusherGui;
    SimpReverb reverbGui;
    MidiKeyboardComp keyboardComponent;
    TextButton keyboardButton;
	TooltipWindow tooltip;
    //Envelope envGui;
    //Frontgui frontGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};

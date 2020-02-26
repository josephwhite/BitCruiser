/*
  ==============================================================================

    Reverb.h
    Created: 26 Feb 2020 9:31:45am
    Author:  Tom Couto

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class SimpReverb    : public Component
{
public:
    SimpReverb(JuceSynthFrameworkAudioProcessor&);
    ~SimpReverb();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider reverbAmount;
    Slider reverbDryWet;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> amountVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetDryVal;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpReverb)
};

/*
  ==============================================================================
    Crusher.h
    Author:  ADMIN
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Crusher : public Component
{
public:
    Crusher(JuceSynthFrameworkAudioProcessor&);
    ~Crusher();

    bool getOnOffState();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider crushDown;
    Slider crushRes;
    ComboBox crushTog;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> crushDownVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> crushResVal;
    ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> crushTogVal;
    
    // This reference is provided as a quick way for your editor to access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Crusher)
};
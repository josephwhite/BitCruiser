/*
  ==============================================================================
    Oscillator3.h
    Author:  ADMIN
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class Oscillator3    : public Component
{
public:
    Oscillator3(JuceSynthFrameworkAudioProcessor&);
    ~Oscillator3();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    ComboBox osc3Menu;
    Slider Blendslider;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection3;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal;
    
    // This reference is provided as a quick way for your editor to access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator3)
};

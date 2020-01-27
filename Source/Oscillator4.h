/*
  ==============================================================================
    Oscillator4.h
    Author:  ADMIN
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class Oscillator4    : public Component
{
public:
    Oscillator4(JuceSynthFrameworkAudioProcessor&);
    ~Oscillator4();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    ComboBox osc4Menu;
    Slider Blendslider;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection4;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal;
    // This reference is provided as a quick way for your editor to access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator4)
};

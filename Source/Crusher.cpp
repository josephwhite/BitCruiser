/*
  ==============================================================================
    Crusher.cpp
    Author:  ADMIN
  ==============================================================================
*/

#include "Crusher.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
Crusher::Crusher(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);

    crushTog.addItem("Off", 1);
    crushTog.addItem("On", 2);
    crushTog.setJustificationType(Justification::centred);
    addAndMakeVisible(&crushTog);
    crushTogVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "crushTog", crushTog);

    crushDown.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    crushDown.setRange(1, 50);
    crushDown.setValue(1);
    crushDown.setTextBoxStyle(Slider::NoTextBox, false, 20, 20);
	crushDown.setTooltip("Diminishes the audio signal per bit.");
    addAndMakeVisible(&crushDown);
    crushDownVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "crushDown", crushDown);
    crushDown.setSkewFactorFromMidPoint(25.0);
    
    crushRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    crushRes.setRange(1, 32);
    crushRes.setValue(32);
    crushRes.setTextBoxStyle(Slider::NoTextBox, false, 20, 20);
	crushRes.setTooltip("Determines how many bits will define the audio signal.");
    addAndMakeVisible(&crushRes);
    crushResVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "crushRes", crushRes);
}

Crusher::~Crusher() {
}

void Crusher::paint (Graphics& g) {
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Crusher", titleArea, Justification::centredTop);
    juce::Rectangle <float> area (25, 25, 100, 150);
    
    g.setColour(Colours::pink);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Crusher::resized() {
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    crushTog.setBounds(area.removeFromTop(20));
    crushDown.setBounds(30, 55, 68, 68);
    crushRes.setBounds(30, 100, 68, 68);
}

/*
  ==============================================================================
    Oscillator3.cpp
    Author:  ADMIN
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator3.h"

//==============================================================================
Oscillator3::Oscillator3(JuceSynthFrameworkAudioProcessor& p) : processor(p) {
    setSize(150, 200);
    osc3Menu.addItem("Saw", 1);
    osc3Menu.addItem("Square", 2);
    osc3Menu.addItem("Sine", 3);
    osc3Menu.addItem("Triangle", 4);
    osc3Menu.setJustificationType(Justification::centred);
    addAndMakeVisible(&osc3Menu);
    
    waveSelection3 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype3", osc3Menu);
    
    //slider initialization values
    Blendslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Blendslider.setRange(0.0f, 1.0f);
    Blendslider.setValue(1.0f);
    Blendslider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&Blendslider);
    
    //sends value of the sliders to the tree state in the processor
    blendVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "blend2", Blendslider);
}

Oscillator3::~Oscillator3()
{
}

void Oscillator3::paint (Graphics& g) {
    //background stuff
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator Three", titleArea, Justification::centredTop);
    
    juce::Rectangle <float> area (25, 25, 100, 150);
    
    g.setColour(Colours::pink);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator3::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    osc3Menu.setBounds(area.removeFromTop(20));
    
    //draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
    int sliderWidth = 20;
    int sliderHeight = 175;
    
    //draw sliders by reducing area from rectangle above
    Blendslider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

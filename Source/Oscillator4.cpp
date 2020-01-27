/*
  ==============================================================================
    Oscillator4.cpp
    Author:  ADMIN
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator4.h"

//==============================================================================
Oscillator4::Oscillator4(JuceSynthFrameworkAudioProcessor& p) : processor(p) {
    setSize(150, 200);
    
    osc4Menu.addItem("Saw", 1);
    osc4Menu.addItem("Square", 2);
    osc4Menu.addItem("Sine", 3);
    osc4Menu.addItem("Triangle", 4);
    osc4Menu.setJustificationType(Justification::centred);
    addAndMakeVisible(&osc4Menu);
    
    waveSelection4 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype4", osc4Menu);
    
    //slider initialization values
    Blendslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Blendslider.setRange(0.0f, 1.0f);
    Blendslider.setValue(1.0f);
    Blendslider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&Blendslider);
    
    //sends value of the sliders to the tree state in the processor
    blendVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "blend3", Blendslider);
}

Oscillator4::~Oscillator4() {
}

void Oscillator4::paint (Graphics& g) {
    //background stuff
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator Four", titleArea, Justification::centredTop);
    
    juce::Rectangle <float> area (25, 25, 100, 150);
    
    g.setColour(Colours::pink);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator4::resized() {
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    osc4Menu.setBounds(area.removeFromTop(20));
    //draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
    int sliderWidth = 20;
    int sliderHeight = 175;
    //draw sliders by reducing area from rectangle above
    Blendslider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

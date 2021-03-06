/*
  ==============================================================================
    Filter.cpp
    Author:  ADMIN
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filterType", filterMenu);
    
    filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0, 10000.0);
    filterCutoff.setValue (400.0);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 30, 30);
    addAndMakeVisible(&filterCutoff);
	filterCutoff.setTooltip("Sets the cutoff frequency.");
    filterVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterCutoff", filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000.0);
    
    filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
	filterRes.setTooltip("Sets the resonance at the cutoff frequency.");
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 30, 30);
    addAndMakeVisible(&filterRes);
    resVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterRes", filterRes);
}

Filter::~Filter() {
}

void Filter::paint (Graphics& g) {
    //background ui stuff
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Filter", titleArea, Justification::centredTop);
    
    juce::Rectangle <float> area (25, 25, 100, 150);
    
    g.setColour(Colours::pink);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized() {
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoff.setBounds (30, 55, 68, 68);
    filterRes.setBounds (30, 100, 68, 68);
}

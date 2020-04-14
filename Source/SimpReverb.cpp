/*
  ==============================================================================
    SimpReverb.cpp
    Author:  Tom Couto
  ==============================================================================
*/

#include "SimpReverb.h"
#include "../JuceLibraryCode/JuceHeader.h"

SimpReverb::SimpReverb(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200,200);

    reverbAmount.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    reverbAmount.setRange(0.0f, 1.0f);
    reverbAmount.setValue (0.5f);
    reverbAmount.setTextBoxStyle(Slider::NoTextBox, false, 30, 30);
    reverbAmount.setTooltip("Sets the amount of reverb.");
    addAndMakeVisible(&reverbAmount);
    amountVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "reverbAmount", reverbAmount);

    reverbDryWet.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    reverbDryWet.setRange(0.0f, 1.0f);
    reverbDryWet.setValue(0.5f);
    reverbDryWet.setTextBoxStyle(Slider::NoTextBox, false, 30, 30);
    reverbAmount.setTooltip("Sets the mix between the wet and dry signals.");
    addAndMakeVisible(&reverbDryWet);
    wetDryVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "reverbDryWet", reverbDryWet);

}

SimpReverb::~SimpReverb() {
}

void SimpReverb::paint (Graphics& g) {
    //background ui stuff
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);

    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Reverb", titleArea, Justification::centredTop);

    juce::Rectangle <float> area (25, 25, 100, 150);

    g.setColour(Colours::pink);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void SimpReverb::resized() {
    //need to come back and dynamically set these...ok for now
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    reverbAmount.setBounds (30, 55, 68, 68);
    reverbDryWet.setBounds (30, 100, 68, 68);
}
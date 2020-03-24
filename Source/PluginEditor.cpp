/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceSynthFrameworkAudioProcessorEditor::JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor& p, MidiKeyboardState& keyboardState)
    : AudioProcessorEditor (&p)
    , processor (p)
    , oscGui(p)
    , osc2Gui(p)
    , osc3Gui(p)
    , osc4Gui(p)
    , filterGui(p)
    , crusherGui(p)
    , reverbGui(p)
    , keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)//, envGui(p), frontGui(p)
{
    setSize (1050, 400);
    
    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&osc2Gui);
    addAndMakeVisible(&osc3Gui);
    addAndMakeVisible(&osc4Gui);
    addAndMakeVisible(&filterGui);
    addAndMakeVisible(&crusherGui);
    addAndMakeVisible(&reverbGui);
    addAndMakeVisible(keyboardComponent);
    addAndMakeVisible(keyboardButton);
    keyboardButton.setButtonText("61");
    keyboardButton.onClick = [this]
    {
        PopupMenu menu;
        menu.addItem(25, "25 keys");
        menu.addItem(37, "37 keys");
        menu.addItem(49, "49 keys");
        menu.addItem(61, "61 keys");
        menu.addItem(88, "88 keys");
        int kc = menu.show();
        if (kc) {
            processor.keyCount = kc;
            keyboardButton.setButtonText(String(kc));
            resized();
        }
    };
}

JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g) {
    g.fillAll(Colours::black);
}

void JuceSynthFrameworkAudioProcessorEditor::resized() {
    juce::Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 150;
    const int componentHeight = 200;
    
    keyboardComponent.setBounds((area.removeFromBottom(componentHeight)));
    switch (processor.keyCount) {
        case 25:
            keyboardComponent.setKeyWidth(area.getWidth() / 15.0f);
            keyboardComponent.setLowestVisibleKey(48);
            break;
        case 37:
            keyboardComponent.setKeyWidth(area.getWidth() / 22.0f);
            keyboardComponent.setLowestVisibleKey(48);
            break;
        case 49:
            keyboardComponent.setKeyWidth(area.getWidth() / 29.0f);
            keyboardComponent.setLowestVisibleKey(36);
            break;
        case 61:
            keyboardComponent.setKeyWidth(area.getWidth() / 36.0f);
            keyboardComponent.setLowestVisibleKey(36);
            break;
        default:
            keyboardComponent.setKeyWidth(area.getWidth() / 52.0f);
            keyboardComponent.setLowestVisibleKey(21);
           break;
    }
    
    oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc2Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc3Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    osc4Gui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    crusherGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    reverbGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}



/*
  ==============================================================================
    SynthVoice.h
    Author:  ADMIN
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice {
public:
    bool canPlaySound (SynthesiserSound* sound) override {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }
    
    void setPitchBend(int pitchWheelPos) {
        if (pitchWheelPos > 8192) {
            // shifting up
            pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
        }
        else {
            // shifting down
            pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
        }
    }

    float pitchBendCents() {
        if (pitchBend >= 0.0f) {
            // shifting up
            return pitchBend * pitchBendUpSemitones * 100;
        }
        else {
            // shifting down
            return pitchBend * pitchBendDownSemitones * 100;
        }
    }

    static double noteHz(int midiNoteNumber, double centsOffset) {
        double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        hertz *= std::pow(2.0, centsOffset / 1200);
        return hertz;
    }

    //=======================================================
    
    void getOscType(float* selection) {
        theWave = *selection;
    }
    void getOsc2Type(float* selection) {
        theWave2 = *selection;
    }
    void getOsc3Type(float* selection) {
        theWave3 = *selection;
    }
    void getOsc4Type(float* selection) {
		theWave4 = *selection;
    }
    //=======================================================
    
    double setOscType () {
        
        double sample1, sample2, sample3, sample4;
        
        switch (theWave) {
            case 0:
                sample1 = osc1.saw(frequency);
                break;
            case 1:
                sample1 = osc1.square(frequency);
                break;
            case 2:
                sample1 = osc1.sinewave(frequency);
                break;
            default:
                sample1 = osc1.triangle(frequency);
                break;
        }
        
        switch (theWave2) {
            case 0:
                sample2 = osc2.saw(frequency / 3.0);
                break;
            case 1:
                sample2 = osc2.square(frequency / 3.0);
                break;
            case 2:
                sample2 = osc2.sinewave(frequency / 3.0);
            default:
                sample2 = osc2.triangle(frequency / 3.0);
                break;
        }
        
        switch (theWave3) {
            case 0:
                sample3 = osc3.saw(frequency / 3.0);
                break;
            case 1:
                sample3 = osc3.square(frequency / 3.0);
                break;
            case 2:
                sample3 = osc3.sinewave(frequency / 3.0);
            default:
                sample3 = osc3.triangle(frequency / 3.0);
                break;
        }
        
        switch (theWave4) {
            case 0:
                sample4 = osc4.saw(frequency / 3.0);
                break;
            case 1:
                sample4 = osc4.square(frequency / 3.0);
                break;
            case 2:
                sample4 = osc4.sinewave(frequency / 3.0);
            default:
                sample4 = osc4.triangle(frequency / 3.0);
                break;
        }
        return sample1 + (osc2blend * sample2) + (osc3blend * sample3) + (osc4blend * sample4);
    }
    
    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release) {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }
    
    double setEnvelope() {
        return env1.adsr(setOscType(), env1.trigger);
    }
    
    void getWillsParams(float* mGain, float* blend, float* blend2, float* blend3, float* pbup, float* pbdn) {
        masterGain = *mGain;
        osc2blend = *blend;
        osc3blend = *blend2;
        osc4blend = *blend3;
        pitchBendUpSemitones = *pbup;
        pitchBendDownSemitones = *pbdn;
    }
    
    void getFilterParams (float* filterType, float* filterCutoff, float* filterRes) {
        filterChoice = *filterType;
        cutoff = *filterCutoff;
        resonance = *filterRes;
    }
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override {
        noteNumber = midiNoteNumber;
        env1.trigger = 1;
        setPitchBend(currentPitchWheelPosition);
        frequency = noteHz(noteNumber, pitchBendCents());
        level = velocity;
    }
    
    void stopNote (float velocity, bool allowTailOff) override {
        env1.trigger = 0;
        allowTailOff = true;
        if (velocity == 0)
            clearCurrentNote();
    }
    
    void pitchWheelMoved (int newPitchWheelValue) override {
        setPitchBend(newPitchWheelValue);
        frequency = noteHz(noteNumber, pitchBendCents());
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue) override {   
    }
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override {
        for (int sample = 0; sample < numSamples; ++sample) {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
                outputBuffer.addSample(channel, startSample, setEnvelope() * masterGain);
            }
            ++startSample;
        }
    }

private:
    double level;
    double frequency;
    int theWave, theWave2, theWave3, theWave4;

    float masterGain;
    float osc2blend;
    float osc3blend;
    float osc4blend;

    int noteNumber;
    float pitchBend = 0.0f;
    float pitchBendUpSemitones = 2.0f;
    float pitchBendDownSemitones = 2.0f;

    int filterChoice;
    float cutoff;
    float resonance;
    
    maxiOsc osc1, osc2, osc3, osc4;
    maxiEnv env1;
};

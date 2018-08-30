/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KhaledverbbAudioProcessorEditor::KhaledverbbAudioProcessorEditor (KhaledverbbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    wetDry.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    wetDry.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 20);
    wetDry.setRange(0.0, 1.0);
    wetDry.addListener(this);
    addAndMakeVisible(wetDry);
    
    roomSize.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    roomSize.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 20);
    roomSize.setRange(0.0, 1.0);
    addAndMakeVisible(roomSize);
    
    damping.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    damping.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 20);
    damping.setRange(0.0, 1.0);
    addAndMakeVisible(damping);
    
    width.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    width.setRange(0, 1.0);
    width.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 20);
    width.addListener(this);
    addAndMakeVisible(width);
    
    setSize (600, 400);
}

KhaledverbbAudioProcessorEditor::~KhaledverbbAudioProcessorEditor()
{
}

//==============================================================================
void KhaledverbbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    getLookAndFeel().setColour(ResizableWindow::backgroundColourId, Colours::burlywood);
    getLookAndFeel().setColour(Slider::ColourIds::thumbColourId, Colours::dimgrey);
    getLookAndFeel().setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    
    
    g.setColour (Colours::black);
    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void KhaledverbbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const int border = 20;
    
    wetDry.setBounds(border, border, getWidth() / 3, getHeight() / 2 - border);
    roomSize.setBounds(border + getWidth() / 3, border, getWidth() / 3, getHeight() / 2 - border);
    damping.setBounds(border + getWidth() * 2 / 3, border, getWidth() / 3, getHeight() / 2 - border);
    width.setBounds(border, border + getHeight()/2, getWidth() - border, getHeight()/2 - border - 30\);
}

void KhaledverbbAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &wetDry) {
        float wet = wetDry.getValue();
        float dry = 1 - wet;
        processor.reverbParameters.dryLevel = dry;
        processor.reverbParameters.wetLevel = wet;
    } else if (slider == &roomSize) {
        processor.reverbParameters.damping = roomSize.getValue();
    } else if (slider == &damping) {
        processor.reverbParameters.damping = damping.getValue();
    } else if (slider == &width) {
        processor.reverbParameters.width = width.getValue();
    }
    
    processor.khaledVerb.setParameters(processor.reverbParameters);
}

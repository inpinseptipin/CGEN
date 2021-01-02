/*
  ==============================================================================

    GeneratorWindow.cpp
    Created: 29 Sep 2020 10:20:37am
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GeneratorWindow.h"

//==============================================================================
GeneratorWindow::GeneratorWindow():DocumentWindow("Generator",juce::Colour(juce::Colours::white), juce::DocumentWindow::closeButton, true)
{
    setSize(400, 300);
    setUsingNativeTitleBar(true);
    centreWithSize(getWidth(), getHeight());
    setResizable(true, false);

}

GeneratorWindow::~GeneratorWindow()
{
}

void GeneratorWindow::paint (juce::Graphics& g)
{
    
}

void GeneratorWindow::resized()
{
 
}

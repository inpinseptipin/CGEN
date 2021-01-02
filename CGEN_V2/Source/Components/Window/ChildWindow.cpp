/*
  ==============================================================================

    ChildWindow.cpp
    Created: 28 Sep 2020 7:24:46pm
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChildWindow.h"

//==============================================================================
ChildWindow::ChildWindow() :
    DocumentWindow("Records", juce::Colour(juce::Colours::white), juce::DocumentWindow::closeButton, true)
{
    setSize(800, 600);
    setUsingNativeTitleBar(true);
    centreWithSize(getWidth(), getHeight());
    setResizable(false, false);

    
}

ChildWindow::~ChildWindow()
{
}

void ChildWindow::paint (juce::Graphics& g)
{
    
}

void ChildWindow::resized()
{
    
}

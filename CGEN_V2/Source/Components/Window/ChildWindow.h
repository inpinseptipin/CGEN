/*
  ==============================================================================

    ChildWindow.h
    Created: 28 Sep 2020 7:24:46pm
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChildWindow  : public juce::DocumentWindow
{
public:
    ChildWindow();
    ~ChildWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void closeButtonPressed()
    {
        setVisible(false);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChildWindow)
};

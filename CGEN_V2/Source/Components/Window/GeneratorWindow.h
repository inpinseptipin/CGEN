/*
  ==============================================================================

    GeneratorWindow.h
    Created: 29 Sep 2020 10:20:37am
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GeneratorWindow  : public juce::DocumentWindow
{
public:
    GeneratorWindow();
    ~GeneratorWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void closeButtonPressed()
    {
        setVisible(false);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GeneratorWindow)
};

/*
  ==============================================================================

    RecordViewer.h
    Created: 28 Sep 2020 7:53:51pm
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Table/Table.h"
#include "../Parsers/CSV.h"

//==============================================================================
/*
*/
class RecordViewer  : public juce::Component
{
public:
    RecordViewer();
    ~RecordViewer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void loadRecords(std::vector<juce::StringArray> &records,const juce::String& fileName);
    CGEN::Table table;

private:
    
    std::vector<juce::StringArray> m_records;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecordViewer)
};

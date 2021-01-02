/*
  ==============================================================================

    GeneratorViewer.h
    Created: 29 Sep 2020 10:08:55am
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Parsers/CSV.h"
#include "../Configuration/config.h"

//==============================================================================
/*
*/
class GeneratorViewer  : public juce::Component
{
public:
    GeneratorViewer();
    ~GeneratorViewer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool checkConfiguration(CGEN::CSV& csv, juce::StringArray configuration);

    void generate();
    void init(std::vector<juce::StringArray> gen,juce::String command,juce::StringArray headers);
    juce::StringArray formatHeader(juce::StringArray& headers);
    void doTask(juce::StringArray headers,uint32_t i);
private:
    juce::TextButton m_openpdf;
    juce::File mf_pdffile;
    juce::Label ml_message;
    std::vector<juce::StringArray> m_records;
    juce::ChildProcess childProcess;

    juce::StringArray m_headers;
    juce::String m_command;
    unsigned int m_recordSize;
    uint32_t certificateNumber;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GeneratorViewer)
};

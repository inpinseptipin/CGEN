/*
  ==============================================================================

    GeneratorViewer.cpp
    Created: 29 Sep 2020 10:08:55am
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GeneratorViewer.h"


//==============================================================================
GeneratorViewer::GeneratorViewer()
{
    setSize(400, 300);

    addAndMakeVisible(m_openpdf);
    m_openpdf.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::black);
    m_openpdf.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::lightgreen);
    m_openpdf.setButtonText("Generate");

    addAndMakeVisible(ml_message);
    ml_message.setColour(juce::Label::ColourIds::textColourId, juce::Colours::red);
    ml_message.setText("", juce::dontSendNotification);
    ml_message.setJustificationType(juce::Justification::horizontallyCentred);
    ml_message.setFont(juce::Font(32.0, 1));

    m_openpdf.onClick = [this]
    {
        ml_message.setText("Starting Generation", juce::dontSendNotification);
        ml_message.setColour(juce::Label::ColourIds::textColourId, juce::Colours::darkgreen);
        generate();
    };
    certificateNumber = 0;

}

GeneratorViewer::~GeneratorViewer()
{
}

void GeneratorViewer::paint (juce::Graphics& g)
{
    
}

void GeneratorViewer::resized()
{
    m_openpdf.setBounds(0, 9*getBottom()/10, getRight(), getBottom() / 10);
    ml_message.setBounds(0, 3*getBottom() / 10, getRight(), 3*getBottom()/10);
}

bool GeneratorViewer::checkConfiguration(CGEN::CSV& csv, juce::StringArray configuration)
{
    juce::StringArray array = csv.getHeader();
    if (array.isEmpty())
    {
        return false;
    }
    if (array == configuration)
    {
        
        return true;
    }
    else
    {
        return false;
    }
}

void GeneratorViewer::generate()
{
    m_openpdf.setEnabled(false);
    m_recordSize = m_records.size();
    certificateNumber = 0;
    for (int i=0;i<m_records.size();i++)
    {
        doTask(formatHeader(m_records[i]),i);
        certificateNumber++;
        ml_message.setText("Generating " + juce::String(certificateNumber) + " of " + juce::String(m_records.size()), juce::dontSendNotification);
    }
    ml_message.setText("Generation Complete", juce::dontSendNotification);
    m_openpdf.setEnabled(true);
}

void GeneratorViewer::doTask(juce::StringArray headers,uint32_t i)
{
    juce::String command = m_command;
    for (auto j = headers.begin(); j != headers.end(); ++j)
    {
        command += *j + " ";
    }
    DBG(command);
    childProcess.start(command, 1);
    DBG(childProcess.readAllProcessOutput());
    
}

void GeneratorViewer::init(std::vector<juce::StringArray> gen,juce::String command,juce::StringArray headers)
{
    m_records = gen;
    m_command = command;
    m_headers = headers;
}

juce::StringArray GeneratorViewer::formatHeader(juce::StringArray& headers)
{
    juce::StringArray m_headers;
    juce::String x;
    for (int i = 0; i < headers.size(); i++)
    {
        x = headers[i];
        x=x.replaceCharacters(" ", "_");
        m_headers.add(x);
    }
    return m_headers;
}

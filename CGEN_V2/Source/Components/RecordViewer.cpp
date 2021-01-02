/*
  ==============================================================================

    RecordViewer.cpp
    Created: 28 Sep 2020 7:53:51pm
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RecordViewer.h"


//==============================================================================
RecordViewer::RecordViewer()
{
    setSize(800, 600);
}

RecordViewer::~RecordViewer()
{
}

void RecordViewer::paint (juce::Graphics& g)
{
   
}

void RecordViewer::resized()
{
    table.setBounds(0, 0, getRight(), getBottom());
}

void RecordViewer::loadRecords(std::vector<juce::StringArray> &records,const juce::String& fileName)
{
    m_records = records;
    table.setNumberOfRows(m_records.size());
    table.setNumberOfColumns(m_records.begin()->size());
    table.initialize();
    for (unsigned int i = 0; i < table.getNumberOfRows(); i++)
    {
        for (unsigned int j = 0; j < table.getNumberOfColumns(); j++)
        {
            table.setCellValue(m_records[i][j], i, j);
        }
    }
    table.setFileName(fileName);
    addAndMakeVisible(table);
    table.makePageVisible(1);
}

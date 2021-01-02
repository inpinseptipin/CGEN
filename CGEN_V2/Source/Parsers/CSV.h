/*
  ==============================================================================

    Student.h
    Created: 24 Aug 2020 3:02:38am
    Author:  Satyarth

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>
namespace CGEN
{
    class CSV
    {
    public:
/*Parses the CSV File and loads it into a 2D String Array*/
        bool parseFile(juce::File& file);

/*Clears the Parsed Data from the 2D String Array*/
        void clearRecords();

/*Return the File Name of the CSV File*/
        juce::String getFileName();

/*Converts the Data to be Converted in a format suitable for IPC*/
        juce::StringArray formatHeader(juce::StringArray &headers);

/*Returns the Column Headings of the CSV File*/
        juce::StringArray getHeader();

/*Returns a reference to the 2D String Array*/
        std::vector<juce::StringArray> getRecords();
    private:
        std::vector<juce::StringArray> m_records;
        juce::String m_fileName;

/*Reads a line from the Stream , and breaks it down into individual Column values*/
        void setItem(juce::String line);
    };

}

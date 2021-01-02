/*
  ==============================================================================

    Student.cpp
    Created: 24 Aug 2020 3:02:38am
    Author:  Satyarth

  ==============================================================================
*/

#include "CSV.h"

namespace CGEN
{
    void CSV::clearRecords()
    {
        for (auto i = m_records.begin(); i != m_records.end(); ++i)
        {
            i->clear();
        }
        m_records.clear();
    }

    void CSV::setItem(juce::String line)
    {
        int start = 0;
        int end = 0;
        juce::StringArray array;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                array.add(line.substring(start, end));
                start = ++end;
            }
            else if(i==line.length()-1)
            {
                array.add(line.substring(start, i+1));
            }
            else
            {
                end++;
            }
        }
        m_records.push_back(array);
    }

    bool CSV::parseFile(juce::File& file)
    {
        clearRecords();
        juce::StringArray temp;
        file.readLines(temp);
        for (auto i = temp.begin(); i != temp.end(); i++)
        {     
            setItem(*i);
        }
        m_fileName = file.getFileName();

        return true;
    }

    std::vector<juce::StringArray> CSV::getRecords()
    {
        return m_records;
    }

    juce::StringArray CSV::getHeader()
    {
        return m_records.front();
    }

    juce::StringArray CSV::formatHeader(juce::StringArray &headers)
    {
        juce::StringArray m_headers;
        juce::String x;
        for (int i = 0; i < headers.size(); i++)
        {
            x = headers[i];
            x.replaceCharacters(" ","_");
            m_headers.add(x);
        }
        return m_headers;
    }

    juce::String CSV::getFileName()
    {
        return m_fileName;
    }

    
};




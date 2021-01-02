/*
  ==============================================================================

    Rows.cpp
    Created: 28 Sep 2020 7:17:28am
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Rows.h"

//==============================================================================

namespace CGEN
{
    //Creates an Empty Row Object
    Rows::Rows()
    {
        m_ncolumns = 0;
        m_columns = nullptr;
        
    }

    //Initalizes Row with number of rows
    void Rows::initialize(uint32_t columns)
    {
        m_ncolumns = columns;
        m_columns = new juce::Label[m_ncolumns];
        
    }

    void Rows::deinitialize()
    {
        if (m_columns != nullptr)
        {
            delete[] m_columns;
            m_columns = nullptr;
        }
    }

    //Deallocates Columns and clears memory
    Rows::~Rows()
    {
        if (m_columns != nullptr)
        {
            delete[] m_columns;
            m_columns = nullptr;
        }
    }

    void Rows::paint(juce::Graphics& g)
    {
        
    }

    //Resizes Rows when Window Size Changes
    void Rows::resized()
    {
        resizeColumns();
    }

    //Resizes the Rows based on Window Size
    void Rows::resizeColumns()
    {
        int width = getRight() / m_ncolumns;
        juce::Label* temp = m_columns;
        for (int i = 0; i < m_ncolumns; i++)
        {
            temp[i].setBounds(width * i, 0, width, getBottom());
        }
    }

    // Sets Value of the Column based on column_id
    void Rows::setColumnValue(const juce::String& value, uint32_t column_id)
    {
        if (m_columns != nullptr && column_id < m_ncolumns)
        {
            m_columns[column_id].setText(value, juce::dontSendNotification);
        }
    }

    // Adds all the Columns and makes them visible
    void Rows::makeAllVisible()
    {
        if (m_columns != nullptr)
        {
            for (int i = 0; i < m_ncolumns; i++)
            {
                m_columns[i].setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::lightgrey);
                m_columns[i].setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::black);
                m_columns[i].setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
                m_columns[i].setFont(juce::Font(16.0,1));
                m_columns[i].setJustificationType(juce::Justification::centredTop);
                addAndMakeVisible(m_columns[i]);
            }
        }
    }

    // Sets Header Properties
    void Rows::setHeaderStyle()
    {
        for (int i = 0; i < m_ncolumns; i++)
        {
            m_columns[i].setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::darkgreen);
            m_columns[i].setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::black);
            m_columns[i].setFont(juce::Font(20,1));
        }
    }

    // Handles Visibility
    void Rows::setColumnVisible(bool flag)
    {
        for (int i = 0; i < m_ncolumns; i++)
        {
            m_columns[i].setVisible(flag);
        }
    }

}



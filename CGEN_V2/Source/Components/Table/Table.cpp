/*
  ==============================================================================

    Table.cpp
    Created: 28 Sep 2020 7:56:37am
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Table.h"

//==============================================================================

namespace CGEN
{
    //Initializes Table Component with Default UI Controls
    Table::Table()
    {
        m_rows = nullptr;
        m_nrows = 1;
        m_ncolumns = 0; 
        DATALOADED = false;

        addChildComponent(mb_prevPage);
        mb_prevPage.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::black);
        mb_prevPage.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::darkorange);
        mb_prevPage.setButtonText("<--");

        addChildComponent(mb_nextPage);
        mb_nextPage.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::black);
        mb_nextPage.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::darkorange);
        mb_nextPage.setButtonText("-->");

        
        addAndMakeVisible(ml_fileName);
        ml_fileName.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::black);
        ml_fileName.setColour(juce::Label::ColourIds::textColourId, juce::Colours::orange);
        ml_fileName.setJustificationType(juce::Justification::horizontallyCentred);
        ml_fileName.setFont(juce::Font(32.0, 1));


        addAndMakeVisible(ml_currentPage);
        ml_currentPage.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::black);
        ml_currentPage.setColour(juce::Label::ColourIds::textColourId, juce::Colours::orange);
        ml_currentPage.setText("1", juce::dontSendNotification);
        ml_currentPage.setJustificationType(juce::Justification::horizontallyCentred);
        


        addAndMakeVisible(ml_header);
        ml_header.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
        ml_header.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::darkblue);
        ml_header.setJustificationType(juce::Justification::horizontallyCentred);
        ml_header.setFont(juce::Font(32.0, 1));
        ml_header.setText("No Data Loaded", juce::dontSendNotification);
        ml_header.setVisible(false);


        mb_prevPage.onClick = [this]
        {
            if (page.getCurrentPage() - 1 > 0)
            {
                if (!mb_nextPage.isVisible())
                    mb_nextPage.setVisible(true);
                makePageVisible(false);
                page.prevPage();
                ml_currentPage.setText(juce::String(page.getCurrentPage()),juce::dontSendNotification);
                makePageVisible(true);
                if (page.getCurrentPage() == 1)
                {
                    mb_prevPage.setVisible(false);
                }
            }
            
        };

        mb_nextPage.onClick = [this]
        {
            if (page.getCurrentPage() + 1 <= page.getTotalPages())
            {
                if (!mb_prevPage.isVisible())
                    mb_prevPage.setVisible(true);
                makePageVisible(false);
                page.nextPage();
                ml_currentPage.setText(juce::String(page.getCurrentPage()),juce::dontSendNotification);
                makePageVisible(true);
                if (page.getCurrentPage() == page.getTotalPages())
                {
                    mb_nextPage.setVisible(false);
                    makePageVisible(true);
                }
            }
        };

        mb_closeTable.onClick = [this]
        {
            ml_currentPage.setText(juce::String(page.getCurrentPage()),juce::dontSendNotification);
        };
      
    }

    //Sets Number of Rows in Tables
    void Table::setNumberOfRows(uint32_t rows)
    {
        m_nrows = rows;
    }

    //Sets Number of Columns in Tables
    void Table::setNumberOfColumns(uint32_t columns)
    {
        m_ncolumns = columns;
    }

    //Gets Number of Rows in Tables
    unsigned int Table::getNumberOfRows()
    {
        return m_nrows;
    }
    
    //Gets Number of Columns in Tables
    unsigned int Table::getNumberOfColumns()
    {
        return m_ncolumns;
    }

    //Initializes Table Structure 
    void Table::initialize()
    {
        DATALOADED = true;
        mb_prevPage.setVisible(false);
        mb_nextPage.setVisible(false);
        m_rows = new CGEN::Rows[m_nrows];
        page.setPages(m_nrows);
        for (int i = 0; i < m_nrows; i++)
        {
                addChildComponent(m_rows[i]);
                m_rows[i].initialize(m_ncolumns);
                m_rows[i].makeAllVisible();
        }
        m_rows[0].setHeaderStyle();
        makePageVisible(true);
        mb_prevPage.setVisible(true);
        mb_nextPage.setVisible(true);
        mb_closeTable.setVisible(true);
        resizeRows();
    }

    //Deinitializes Table Structure
    void Table::deinitialize()
    {
        DATALOADED = false;
        makePageVisible(false);
        mb_nextPage.setVisible(false);
        mb_prevPage.setVisible(false);
        mb_closeTable.setVisible(false);
        ml_header.setVisible(true);
        if (m_rows != nullptr)
        {
            delete[] m_rows;
            m_rows = nullptr;
        }

    }

    //Destructor : Frees Table's Heap Memory
    Table::~Table()
    {
        if (m_rows != nullptr)
        {
            delete[] m_rows;
            m_rows = nullptr;
        }
    }


    void Table::paint(juce::Graphics& g)
    {
        g.setColour(juce::Colours::darkviolet);
        g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

        g.setColour(juce::Colours::black);
        g.fillAll();
        
    }

    //Called when Window is Resized
    void Table::resized()
    {
        resizeRows();
    }

   
    //Resizes Table UI and Rows and Columns
    void Table::resizeRows()
    {
        if (DATALOADED)
        {
            int height = (7 * getBottom() / 10) / 8;
            int x = 0;
            CGEN::Rows* temp = m_rows;
            for (unsigned int i = page.Start(); i < page.End(); i++)
            {
                temp[i].setBounds(0, getBottom()/10 + (height * x), getRight(), height);
                x++;
            }
            ml_fileName.setBounds(0, 0, 15 * getRight() / 16, getBottom() / 10);
            ml_currentPage.setBounds(15 *getRight() / 16, 0, getRight() / 16, getBottom() / 10);
            mb_prevPage.setBounds(3 * getRight() / 4, 8*getBottom()/10, getRight() / 8, getBottom() / 10);
            mb_nextPage.setBounds(3 * getRight() / 4 + getRight() / 8, 8 * getBottom() / 10, getRight() / 8, getBottom() / 10);
            
        }
        else if (!DATALOADED)
        {
            ml_header.setBounds(0, 0, getRight(), getBottom());
        }
                    
    }
    
    //Sets Value to Table(row,column) 
    void Table::setCellValue(juce::String value,uint32_t row_id, uint32_t column_id)
    {
        if (m_rows != nullptr)
        {
            m_rows[row_id].setColumnValue(value, column_id);
        }
    }

    //Handles Table's Rows Visibility
    void Table::makeRowsVisible(bool setVisible)
    {
        if (m_rows != nullptr)
        {
            CGEN::Rows* temp = m_rows;
            for (int i = 0; i < m_nrows; i++)
            {
                temp[i].setVisible(setVisible);
            }
        }
    }

    //Handles Current Page Visibility
    void Table::makePageVisible(bool setVisible)
    {
        CGEN::Rows* temp = m_rows;
        for (int i = page.Start(); i < page.End(); i++)
        {
            temp[i].setVisible(setVisible);
        }
        resizeRows();
    }

    void Table::setFileName(const juce::String& filename)
    {
        ml_fileName.setText(filename, juce::dontSendNotification);
    }
 
//==============================================================================

    Page::Page()
    {
        m_pages = 0;
        m_currentPage = 0;
        m_start = 0;
        m_end = 0;
        m_diff = 0;
    }

    Page::~Page()
    {
    
    }

    void Page::setPages(uint32_t rows)
    {
        jassert(rows > 0);
        m_pages = rows / 8;
        if (rows % 8 > 0)
        {
            m_diff = rows % 8;
            m_pages++;
        }
        else
        {
            m_diff = 0;
        }
        m_currentPage = 1;
        m_start = 0;
        m_end = 8;
    }

    void Page::jumpToPage(uint32_t pageNumber)
    {
        jassert(pageNumber <= m_pages);
        m_currentPage = pageNumber;

        if (m_currentPage == m_pages)
        {
            m_start = (m_currentPage - 1) * 8;
            m_end = m_start + (m_diff-1);
        }
        else
        {
            m_start = (m_currentPage - 1) * 8;
            m_end = m_start + 8;
        }
    }

    unsigned int Page::Start()
    {
        return m_start;
    }

    unsigned int Page::End()
    {
        return m_end;
    }

    void Page::prevPage()
    {
        jumpToPage(m_currentPage - 1);
    }

    void Page::nextPage()
    {
        jumpToPage(m_currentPage + 1);
    }

    unsigned int Page::getCurrentPage()
    {
        return m_currentPage;
    }

    unsigned int Page::getTotalPages()
    {
        return m_pages;
    }

}

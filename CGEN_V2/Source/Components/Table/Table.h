/*
  ==============================================================================

    Table.h
    Created: 28 Sep 2020 7:56:37am
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Rows.h"

//==============================================================================
/*
*/
namespace CGEN
{
    
    class Page
    {
    public:
        Page();
        ~Page();

        void setPages(uint32_t rows);
        void jumpToPage(uint32_t pageNumber);
        void nextPage();
        void prevPage();
        uint32_t getCurrentPage();
        uint32_t getTotalPages();
        uint32_t Start();
        uint32_t End();

    private:
        uint32_t m_pages;
        uint32_t m_currentPage;
        uint32_t m_start;
        uint32_t m_end;
        uint32_t m_diff;
    };

    class Table : public juce::Component
    {
    public:
        Table();
        ~Table() override;
        void initialize();
        void deinitialize();
        void paint(juce::Graphics&) override;
        void resized() override;
        void resizeRows();
        void setNumberOfRows(uint32_t rows);
        void setNumberOfColumns(uint32_t columns);
        void setFileName(const juce::String& filename);
        uint32_t getNumberOfRows();
        uint32_t getNumberOfColumns();
        void setCellValue(juce::String value,uint32_t row_id, uint32_t column_id);
        void makeRowsVisible(bool setVisible);
        void makePageVisible(bool setVisible);
    private:
        CGEN::Rows* m_rows;
        uint32_t m_nrows;
        uint32_t m_ncolumns;
        bool DATALOADED;
        Page page;
        juce::TextButton mb_nextPage;
        juce::TextButton mb_prevPage;
        juce::TextButton mb_closeTable;
        juce::Label ml_currentPage;
        juce::Label ml_header;
        juce::Label ml_fileName;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Table)
    };

}

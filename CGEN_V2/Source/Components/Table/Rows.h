/*
  ==============================================================================

    Rows.h
    Created: 28 Sep 2020 7:17:28am
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
namespace CGEN
{
    class Rows : public juce::Component
    {
    public:
        Rows();
        ~Rows() override;
        void paint(juce::Graphics&) override;
        void resized() override;
        void initialize(uint32_t columns);
        void deinitialize();
        void setHeaderStyle();
        void resizeColumns();
        void setColumnValue(const juce::String& value, uint32_t column_id);
        void makeAllVisible();
        void setColumnVisible(bool flag);
    private:
        juce::Label* m_columns;
        uint32_t m_ncolumns;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Rows)
    };
}


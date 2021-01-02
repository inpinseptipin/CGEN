#pragma once

#include <JuceHeader.h>
#include "Configuration/config.h"
#include "Components/Table/Rows.h"
#include "Components/Table/Table.h"
#include "Parsers/CSV.h"
#include "Components/Window/ChildWindow.h"
#include "Components/RecordViewer.h"
#include "Components/GeneratorViewer.h"
#include "Components/Window/GeneratorWindow.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/



class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    

    void initConfiguration();

private:
    //==============================================================================
    // Your private member variables go here...
    CGEN::Table table;
    CGEN::CSV csv;
    bool GENERATEFLAG;
    
    //=================================Child Windows================================
    std::unique_ptr<ChildWindow> childWindow;
    std::unique_ptr<GeneratorWindow> generatorWindow;
    std::unique_ptr<RecordViewer> recordViewer;
    std::unique_ptr<GeneratorViewer> generatorViewer;
    
    //=================================Child Windows================================
    juce::TextButton mb_open;
    juce::TextButton mb_loadFile;
    juce::Label ml_header;
    juce::Label ml_configheader;
    juce::Label ml_message;
    juce::ComboBox mc_config;
    juce::TextButton mb_generate;
    //=================================Methods=======================================
    CGEN::CertificateConfiguration m_config;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

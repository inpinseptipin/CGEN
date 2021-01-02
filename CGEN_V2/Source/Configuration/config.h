/*
  ==============================================================================

    config.h
    Created: 9 Oct 2020 7:24:36pm
    Author:  arsen

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>
#include<vector>
namespace CGEN
{
    class CertificateConfiguration
    {
    private:
        struct config
        {
            uint32_t m_no;
            juce::String m_name;
            juce::StringArray m_headers;
            juce::String m_command;
        };
        uint32_t m_no;
        
        std::vector<config> m_config;
    public: 
        CertificateConfiguration();
        CertificateConfiguration(uint32_t noOfConfigs);
        juce::StringArray getConfiguration(juce::String name);
        juce::StringArray getConfigNames();
        juce::String getConfigurationCommand(juce::String name);
        void addValue(juce::String name, juce::StringArray headers, juce::String command);
        
    };
}

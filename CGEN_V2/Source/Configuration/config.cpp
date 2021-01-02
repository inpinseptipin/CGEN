/*
  ==============================================================================

    config.cpp
    Created: 9 Oct 2020 7:24:36pm
    Author:  arsen

  ==============================================================================
*/

#include "config.h"


namespace CGEN
{
    CertificateConfiguration::CertificateConfiguration()
    {
        m_no = 0;
    }

    CertificateConfiguration::CertificateConfiguration(uint32_t noOfConfigs)
    {
        m_no = 0;
        m_config.resize(noOfConfigs);
    }

    void CertificateConfiguration::addValue(juce::String name, juce::StringArray headers, juce::String command)
    {
        m_config.resize(m_no + 1);
        m_config[m_no].m_no = m_no;
        m_config[m_no].m_name = name;
        m_config[m_no].m_command = command;
        m_config[m_no].m_headers = headers;
        m_no++;
    }

    juce::StringArray CertificateConfiguration::getConfiguration(juce::String name)
    {
        for (auto i = m_config.begin(); i != m_config.end(); ++i)
        {
            if (i->m_name == name)
            {
                return i->m_headers;
            }
        }
    }

    juce::StringArray CertificateConfiguration::getConfigNames()
    {
        juce::StringArray names;
        for (auto i = m_config.begin(); i != m_config.end(); ++i)
        {
            names.add(i->m_name);
        }
        return names;
    }

    juce::String CertificateConfiguration::getConfigurationCommand(juce::String name)
    {
        for (auto i = m_config.begin(); i != m_config.end(); ++i)
        {
            if (i->m_name == name)
            {
                return i->m_command;
            }
        }
    }

}

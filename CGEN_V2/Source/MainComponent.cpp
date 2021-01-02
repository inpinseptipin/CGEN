#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    childWindow.reset(new ChildWindow);
    generatorWindow.reset(new GeneratorWindow);

    initConfiguration();

    GENERATEFLAG = false;
    

    addAndMakeVisible(ml_header);
    ml_header.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::darkblue);
    ml_header.setColour(juce::Label::ColourIds::textColourId, juce::Colours::green);
    ml_header.setText("CGEN Version 1.2", juce::dontSendNotification);
    ml_header.setFont(juce::Font(32.0, 1));
    ml_header.setJustificationType(juce::Justification::horizontallyCentred);

    addAndMakeVisible(ml_configheader);
    ml_configheader.setColour(juce::Label::ColourIds::textColourId, juce::Colours::green);
    ml_configheader.setFont(juce::Font(16.0, 1));
    ml_configheader.setJustificationType(juce::Justification::horizontallyCentred);

    addAndMakeVisible(ml_message);
    ml_message.setColour(juce::Label::ColourIds::textColourId, juce::Colours::red);
    ml_message.setFont(juce::Font(16.0, 1));
    ml_message.setJustificationType(juce::Justification::horizontallyCentred);

    addAndMakeVisible(mc_config);
    mc_config.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::green);
    mc_config.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::white);
    mc_config.setJustificationType(juce::Justification::horizontallyCentred);
    mc_config.setTextWhenNothingSelected("Choose Certificate Configuration");
    mc_config.setEditableText(false);

   



    addAndMakeVisible(mb_generate);
    mb_generate.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::green);
    mb_generate.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::white);
    mb_generate.setButtonText("Generate");
    mb_generate.setEnabled(false);

    addAndMakeVisible(mb_open);
    mb_open.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::green);
    mb_open.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::white);
    mb_open.setButtonText("See All Records");
    mb_open.setEnabled(false);


    addAndMakeVisible(mb_loadFile);
    mb_loadFile.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::green);
    mb_loadFile.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::white);
    mb_loadFile.setButtonText("Load Records");


    mc_config.onChange = [this]
    {
        juce::StringArray array = m_config.getConfiguration(mc_config.getText());
        juce::String headers = "Headers \n ";
        for (int i = 0; i < array.size(); i++)
        {
            headers += array[i] + ",";
        }
        ml_configheader.setText(headers, juce::dontSendNotification);
    };
    
    mb_open.onClick = [this]
    {
        recordViewer.reset(new RecordViewer);
        recordViewer->loadRecords(csv.getRecords(),csv.getFileName());
        childWindow->setContentOwned(recordViewer.get(),true);
        childWindow->setVisible(true);
       
    };

    mb_loadFile.onClick = [this]
    {
        juce::FileChooser chooser("Select Records File", {}, "*.csv");
        if (chooser.browseForFileToOpen())
        {
            mb_generate.setEnabled(true);
            csv.parseFile(chooser.getResult());
            mb_open.setEnabled(true);
        }
        else
        {
            mb_open.setEnabled(false);
            DBG("No File Choosen");
        }
    };

    mb_generate.onClick = [this]
    {
        if (generatorViewer->checkConfiguration(csv, m_config.getConfiguration(mc_config.getText())))
        {
            generatorViewer.reset(new GeneratorViewer());
            generatorViewer->init(csv.getRecords(),m_config.getConfigurationCommand(mc_config.getText()),m_config.getConfiguration(mc_config.getText()));
            generatorWindow->setContentOwned(generatorViewer.get(), true);
            generatorWindow->setVisible(true);
            ml_message.setText("Configuration Matched", juce::dontSendNotification);
            ml_message.setColour(juce::Label::ColourIds::textColourId, juce::Colours::darkgreen);
        }
        else
        {
            ml_message.setText("Configurations Do not Match",juce::dontSendNotification);
        }
        
    };

}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
}

void MainComponent::resized()
{
    ml_header.setBounds(0, 0, getRight(), getBottom() / 10);
    mb_loadFile.setBounds(0, 2 * getBottom() / 10, getRight() / 2, getBottom() / 10);
    mb_open.setBounds(0, 4 * getBottom() / 10, getRight() / 2, getBottom() / 10);
    mc_config.setBounds(0, 6 * getBottom() / 10, getRight() / 2, getBottom() / 10);
    mb_generate.setBounds(0, 8 * getBottom() / 10, getRight() / 2, getBottom() / 10);
    ml_configheader.setBounds(getRight() / 2, 6 * getBottom() / 10, getRight() / 2, getBottom() / 10);
    ml_message.setBounds(getRight() / 2, 8 * getBottom() / 10, getRight() / 2, getBottom() / 10);

}

void MainComponent::initConfiguration()
{
    m_config.addValue("Scholar Badge", { "Name","Class","S_Class","Session" },"python scholar.py ");
    m_config.addValue("Super Scholar", { "Name","Class","Section","Session","S_Class" }, "python superscholar.py ");
    m_config.addValue("Upto Five Percent", { "Name","Class","Section","Session","S_Class" }, "python fivepercent.py ");
    m_config.addValue("Greater Than Five Percent", { "Name","Class","Section","Session","S_Class" }, "python fivepercent_2.py ");
    m_config.addValue("Medal", { "Name","Class","Section","Session","S_Class" }, "python medal.py ");
    m_config.addValue("CV Raman Participant", { "Name","Class","School","Date","Marks" }, "python participant.py ");
    m_config.addValue("CV Raman Appreciate", { "Name","Class","School","Date","Marks" }, "python appreciation.py ");
    mc_config.addItemList(m_config.getConfigNames(), 1);
}







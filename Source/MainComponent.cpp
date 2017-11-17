/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent(String name) : vt(Ids::TRANSCRIPTFILE)
{
    fileTransport = new AudioFileTransportComponent();
    
    addAndMakeVisible(fileTransport);
    menuBar.setModel(this);
    addAndMakeVisible(menuBar);
    
    addAndMakeVisible(editor);
    
    
    
    addKeyListener(fileTransport);

    editor.addKeyListener(fileTransport);
    addKeyListener(this);
    editor.setMultiLine(true);
    editor.setEscapeAndReturnKeysConsumed(true);
    editor.setReturnKeyStartsNewLine(true);
    
    setValueTree(name);
    
    setSize (800, 800);
}

MainContentComponent::~MainContentComponent()
{
    listeners.clear();
}

void MainContentComponent::paint (Graphics& g)
{

}

void MainContentComponent::resized()
{
    
    auto area (getLocalBounds());
    menuBar.setBounds(area.removeFromTop(20));
    fileTransport->setBounds(area.removeFromTop(100));

    
    editor.setBounds(area);
}
void MainContentComponent:: saveValueTree()
{
    File saveFile;
    if (vt.getProperty(Ids::filePath).toString().isEmpty())
    {
        FileChooser saveFileChooser ("Select a file to save...", File::getSpecialLocation(File::userDesktopDirectory),"trnscrpt");
        if (saveFileChooser.browseForFileToSave(true))
        {
            saveFile = saveFileChooser.getResult();
            vt.setProperty(Ids::filePath, saveFile.getFullPathName(), nullptr);
            
        }
    }
    else {
        saveFile = File(vt.getProperty(Ids::filePath));
    }
    
    vt.setProperty(Ids::text, editor.getText(), nullptr);
    
    DBG(saveFile.getFullPathName());
    saveFile.deleteFile();
    FileOutputStream fos(saveFile);
    vt.writeToStream(fos);
    DBG(vt.toXmlString());
    
}
void MainContentComponent::openValueTree()
{
    if (saveBeforeClosing())
    {
        FileChooser chooser("Select File to Open...", File::getSpecialLocation(File::userDesktopDirectory),"*.trnscrpt");
        if (chooser.browseForFileToOpen())
        {
            String result = chooser.getResult().getFullPathName();
            setValueTree(result);
            
            
        }
    }
}
void MainContentComponent::newValueTree()
{
    if (saveBeforeClosing())
    {
        setValueTree();
    }
}
bool MainContentComponent::saveBeforeClosing()
{
    AlertWindow aw ("Alert!", "Do you wish to save before opening a new file?", AlertWindow::WarningIcon, nullptr);
    aw.addButton("Yes", 0);
    aw.addButton("No", 1);
    aw.addButton("Cancel", 2);
    
    int result = aw.runModalLoop();
    
    if (result == 0)
    {
        saveValueTree();
        return true;
    }
    else if (result == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
void MainContentComponent::setValueTree(const String filename_)
{
    DBG(filename_);
    if (filename_.isEmpty())
    {
        vt.setProperty(Ids::audioFile, String::empty, nullptr);
        vt.setProperty(Ids::audioFilePos, 0, nullptr);
        vt.setProperty(Ids::filePath, String::empty, nullptr);
        vt.setProperty(Ids::text, String::empty, nullptr);
    }
    
    else
    {
        File toOpen(filename_);
        jassert(toOpen.existsAsFile());
        FileInputStream fis(toOpen);
        vt = ValueTree::readFromStream(fis);
        
    }
    editor.setText(vt.getProperty(Ids::text).toString());
    fileTransport->setValueTree(vt);
    DBG(vt.toXmlString());
    
    listeners.call(&Listener::fileNameChanged, filename_);
}
void MainContentComponent::timerCallback()
{
    vt.setProperty(Ids::text, editor.getText(), nullptr);
}

bool MainContentComponent:: keyPressed (const KeyPress& key,
                 Component* originatingComponent)
{
    if (key.getModifiers().isCommandDown())
    {
        DBG("KeyPressed " << key.getKeyCode());
        if (key.getKeyCode() == 83)
        {
            saveValueTree();
            return true;
        }
        else if (key.getKeyCode() == 79)
        {
            openValueTree();
            return true;
        }
        else if (key.getKeyCode() == 78)
        {
            newValueTree();
            return true;
        }
    }
    return false;
}
StringArray MainContentComponent:: getMenuBarNames()
{
    return {"File","Preferences"};
}

PopupMenu MainContentComponent:: getMenuForIndex (int topLevelMenuIndex,
                           const String& menuName)
{
    PopupMenu menu;
    if (topLevelMenuIndex == 0)
    {
        menu.addItem(1, "New... (cmd + N)");
        menu.addItem(2, "Open... (cmd + O)");
        menu.addItem(3, "Save... (cmd + S)");
    }
    return menu;
}

void MainContentComponent:: menuItemSelected (int menuItemID,
                       int topLevelMenuIndex)
{
    switch (menuItemID)
    {
        case 1:
            newValueTree();
            break;
        case 2:
            openValueTree();
            break;
        case 3:
            saveValueTree();
            break;
        
        default:
            break;
    }
}

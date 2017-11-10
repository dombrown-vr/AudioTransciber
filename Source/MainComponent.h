/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Audio.h"
#include "AudioFileTransportComponent.h"
#include "Ids.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, public Timer, public KeyListener, public MenuBarModel
{
public:
    //==============================================================================
    MainContentComponent(String name);
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void setValueTree(const String filename = String::empty);

    void saveValueTree();
    void openValueTree();
    void newValueTree();
    void updateValueTree();
    
    void timerCallback();
    
    bool keyPressed (const KeyPress& key,
                     Component* originatingComponent) override;
    
    StringArray getMenuBarNames() override;
    
    PopupMenu getMenuForIndex (int topLevelMenuIndex,
                               const String& menuName) override;
    
    void menuItemSelected (int menuItemID,
                           int topLevelMenuIndex) override;
    
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void fileNameChanged(String name_) {}
    };
    
    void addListener(Listener* toAdd)
    {
        listeners.add(toAdd);
    }
    
private:
    bool saveBeforeClosing();
    
    MenuBarComponent menuBar;
    Audio audio;
    AudioFileTransportComponent aftc;
    TextEditor editor;
    ListenerList<Listener> listeners;
    
    ValueTree vt;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

//
//  FileTransportComponent.h
//  AudioTranscriber
//
//  Created by Dominic Brown on 11/11/2017.
//
//

#ifndef __AudioTranscriber__FileTransportComponent__
#define __AudioTranscriber__FileTransportComponent__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

class FileTransportComponent : public Component, public Slider::Listener, public Button::Listener, public KeyListener, public Timer
{
public:
    FileTransportComponent() {}
    virtual ~FileTransportComponent() {}
    
    virtual void setValueTree(ValueTree vt_) {vt = vt_;}
    
protected:
    TextButton loadFileButton, playButton, stopButton, pauseButton;
    Slider transportSlider;
    ValueTree vt;
};


#endif /* defined(__AudioTranscriber__FileTransportComponent__) */

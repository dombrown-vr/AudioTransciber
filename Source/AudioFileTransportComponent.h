//
//  AudioFileTransportComponent.h
//  AudioTranscriber
//
//  Created by Dominic Brown on 10/11/2017.
//
//

#ifndef __AudioTranscriber__AudioFileTransportComponent__
#define __AudioTranscriber__AudioFileTransportComponent__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Audio.h"
#include "FileTransportComponent.h"

class AudioFileTransportComponent : public FileTransportComponent, public Audio::Listener
{
public:
    AudioFileTransportComponent();
    ~AudioFileTransportComponent();
    
    void sliderValueChanged(Slider* slider) override;
    
    void buttonClicked(Button* button) override;
    
    bool keyPressed (const KeyPress& key,
                     Component* originatingComponent) override;
    
    void audioFileUpdated(int64 fileLength) override;
    
    void setValueTree(ValueTree vt) override;
    
    void resized() override;
    
private:
    
    void timerCallback() override;
    
    
    
    Audio audio;
    TextButton loadFileButton, playButton, stopButton, pauseButton;
    Slider transportSlider, speedSlider;
    
};

#endif /* defined(__AudioTranscriber__AudioFileTransportComponent__) */

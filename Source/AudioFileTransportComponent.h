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

class AudioFileTransportComponent : public Component, public Slider::Listener, public Button::Listener, public Timer, public KeyListener, public Audio::Listener
{
public:
    AudioFileTransportComponent(Audio& a);
    ~AudioFileTransportComponent();
    
    void sliderValueChanged(Slider* slider) override;
    
    void buttonClicked(Button* button) override;
    
    bool keyPressed (const KeyPress& key,
                     Component* originatingComponent) override;
    
    void audioFileUpdated(int64 fileLength) override;
    
private:
    
    void timerCallback() override;
    
    void resized() override;
    
    Audio& audio;
    TextButton loadFileButton, playButton, stopButton, pauseButton;
    Slider transportSlider;
    
};

#endif /* defined(__AudioTranscriber__AudioFileTransportComponent__) */

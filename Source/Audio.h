//
//  Audio.h
//  AudioTranscriber
//
//  Created by Dominic Brown on 10/11/2017.
//
//

#ifndef __AudioTranscriber__Audio__
#define __AudioTranscriber__Audio__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Ids.h"

class Audio
{
    
public:
    
    Audio();
    ~Audio();
    
    void setFile (const File audioFile_);
    
    void setFile(const String audioFileName_);
    
    void setValueTree(ValueTree);
    
    void startPlaying();
    void stopPlaying();
    void pausePlaying();
    
    void setPosition(double pos);
    double getPosition();
    
    void setPlaybackSpeed(double speed_);
    double getPlaybackSpeed();
    
    void togglePlaying();
    
    AudioFormatManager fm;
    
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void audioFileUpdated(int64 fileLength) {}
    };
    void addListener(Listener* toAdd);
    
private:
    ScopedPointer<AudioFormatReaderSource> audioFileSource;
    ScopedPointer<AudioTransportSource> transportSource;
    ScopedPointer<ResamplingAudioSource> resamplingSource;
    
    AudioDeviceManager adm;
    AudioSourcePlayer player;
    ValueTree vt;
    ListenerList<Listener> listeners;
    File currentFile;
    CriticalSection listenerLock;
};


#endif /* defined(__AudioTranscriber__Audio__) */

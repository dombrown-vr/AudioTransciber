//
//  Audio.cpp
//  AudioTranscriber
//
//  Created by Dominic Brown on 10/11/2017.
//
//

#include "Audio.h"


Audio::Audio()
{
    fm.registerBasicFormats();

    transportSource = new AudioTransportSource();
   
    adm.addAudioCallback(&player);
    adm.initialiseWithDefaultDevices(0, 2);
    resamplingSource = new ResamplingAudioSource(transportSource, false);
     player.setSource(resamplingSource);
    
}
Audio::~Audio()
{
    listeners.clear();
    transportSource->releaseResources();
    adm.removeAudioCallback(&player);
}
void Audio::setFile(const File audioFile_)
{
    DBG(audioFile_.getFullPathName());

        transportSource->stop();
        audioFileSource = nullptr;
    ScopedPointer<AudioFormatReaderSource> afrs = new AudioFormatReaderSource(fm.createReaderFor(audioFile_), true);
    audioFileSource = afrs.release();
        transportSource->setSource(audioFileSource);
        vt.setProperty(Ids::audioFile, audioFile_.getFullPathName(), nullptr);
        listeners.call(&Listener::audioFileUpdated, transportSource->getTotalLength()/adm.getCurrentAudioDevice()->getCurrentSampleRate());
        currentFile = audioFile_;
}
void Audio::setFile(const String audioFileName_)
{
    if (audioFileName_.isNotEmpty())
    {
        File audioFile(audioFileName_);
        setFile(audioFile);
    }
    else
    {
        DBG("Error! file name is empty");
    }
}
void Audio::startPlaying()
{
    transportSource->start();
}
void Audio::stopPlaying()
{
    transportSource->stop();
    setPosition(0.0);
}
void Audio::pausePlaying()
{
    transportSource->stop();
}
void Audio::setPosition(double pos)
{
    DBG("new position: " << pos);
    if (pos >= 0 && pos < transportSource->getTotalLength())
    {
        transportSource->setPosition(pos);
    }
    else if (pos < 0)
    {
        transportSource->setPosition(0.0);
    }
    vt.setProperty(Ids::audioFilePos, transportSource->getCurrentPosition(), nullptr);
}
double Audio::getPosition()
{
    double pos = transportSource->getCurrentPosition();
    vt.setProperty(Ids::audioFilePos, pos, nullptr);
    return pos;
}
void Audio::setValueTree(ValueTree vt_)
{
    vt = vt_;
    String audioFile = vt.getProperty(Ids::audioFile);
    setFile(audioFile);
    setPosition(vt.getProperty(Ids::audioFilePos,0.0));
    setPlaybackSpeed(vt.getProperty(Ids::playbackSpeed,1.0));
}
void Audio::addListener(Listener* toAdd)
{
    ScopedLock sl(listenerLock);
    listeners.add(toAdd);
}

void Audio::setPlaybackSpeed(double speed_)
{
    resamplingSource->setResamplingRatio(speed_);
    vt.setProperty(Ids::playbackSpeed, speed_, nullptr);
}
double Audio::getPlaybackSpeed()
{
    return resamplingSource->getResamplingRatio();
}
void Audio::togglePlaying()
{
    DBG("toggled");
    if (transportSource->isPlaying())
    {
        pausePlaying();
        DBG("paused");
    }
    else
    {
        startPlaying();
        DBG("started");
        
    }
}

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

    source = new AudioTransportSource();
    player.setSource(source);
    adm.addAudioCallback(&player);
    adm.initialiseWithDefaultDevices(0, 2);
    
}
Audio::~Audio()
{
    listeners.clear();
    source->releaseResources();
    adm.removeAudioCallback(&player);
}
void Audio::setFile(const File audioFile_)
{
    DBG(audioFile_.getFullPathName());
//    if (currentFile != audioFile_)
//    {
        source->stop();
        //    source->releaseResources();
        audioFileSource = nullptr;
        audioFileSource = new AudioFormatReaderSource(fm.createReaderFor(audioFile_), true);
        source->setSource(audioFileSource);
        vt.setProperty(Ids::audioFile, audioFile_.getFullPathName(), nullptr);
        listeners.call(&Listener::audioFileUpdated, source->getTotalLength()/adm.getCurrentAudioDevice()->getCurrentSampleRate());
        currentFile = audioFile_;
//    }
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
    source->start();
}
void Audio::stopPlaying()
{
    source->stop();
    setPosition(0.0);
}
void Audio::pausePlaying()
{
    source->stop();
}
void Audio::setPosition(double pos)
{
    DBG("new position: " << pos);
    if (pos >= 0 && pos < source->getTotalLength())
    {
        source->setPosition(pos);
    }
    else if (pos < 0)
    {
        source->setPosition(0.0);
    }
    vt.setProperty(Ids::audioFilePos, source->getCurrentPosition(), nullptr);
}
double Audio::getPosition()
{
    double pos = source->getCurrentPosition();
    vt.setProperty(Ids::audioFilePos, pos, nullptr);
    return pos;
}
void Audio::setValueTree(ValueTree vt_)
{
    vt = vt_;
    String audioFile = vt.getProperty(Ids::audioFile);
    setFile(audioFile);
    setPosition(vt.getProperty(Ids::audioFilePos));
}
void Audio::addListener(Listener* toAdd)
{
    ScopedLock sl(listenerLock);
    listeners.add(toAdd);
}

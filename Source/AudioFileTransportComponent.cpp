//
//  AudioFileTransportComponent.cpp
//  AudioTranscriber
//
//  Created by Dominic Brown on 10/11/2017.
//
//

#include "AudioFileTransportComponent.h"

AudioFileTransportComponent::AudioFileTransportComponent(Audio& a) : audio(a)
{
    transportSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    transportSlider.setRange(0.0, 1.0);
    addAndMakeVisible(transportSlider);
    transportSlider.addListener(this);
    
    playButton.setButtonText(">");
    playButton.addListener(this);
    addAndMakeVisible(playButton);
    
    pauseButton.setButtonText("||");
    pauseButton.addListener(this);
    addAndMakeVisible(pauseButton);
    
    stopButton.setButtonText("[]");
    stopButton.addListener(this);
    addAndMakeVisible(stopButton);
    
    loadFileButton.setButtonText("Load");
    loadFileButton.addListener(this);
    addAndMakeVisible(loadFileButton);
    
    addKeyListener(this);
//    setWantsKeyboardFocus(true);
    startTimer(50);
    audio.addListener(this);
    
    
}
AudioFileTransportComponent::~AudioFileTransportComponent()
{
    stopTimer();
}
void AudioFileTransportComponent::resized()
{
    auto area(getLocalBounds());
    
    transportSlider.setBounds(area.removeFromTop(getHeight()/2));
    
    int width = std::min(getWidth()/4,150);
    loadFileButton.setBounds(area.removeFromLeft(width));
    playButton.setBounds(area.removeFromLeft(width));
    pauseButton.setBounds(area.removeFromLeft(width));
    stopButton.setBounds(area.removeFromLeft(width));
    
}
void AudioFileTransportComponent::sliderValueChanged(Slider* slider)
{
    if (slider == &transportSlider)
    {
        audio.setPosition(slider->getValue());
    }
}
void AudioFileTransportComponent::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        audio.startPlaying();
    }
    else if (button == &stopButton)
    {
        audio.stopPlaying();
    }
    else if (button == &pauseButton)
    {
        audio.pausePlaying();
    }
    else if (button == &loadFileButton)
    {
        FileChooser fileChooser ("Choose a file...", File::getSpecialLocation(File::userDesktopDirectory),audio.fm.getWildcardForAllFormats());
        
        if(fileChooser.browseForFileToOpen())
        {
            audio.setFile(fileChooser.getResult());
            
        }
    }
}
void AudioFileTransportComponent::timerCallback()
{
    transportSlider.setValue( audio.getPosition(),dontSendNotification);
}
bool AudioFileTransportComponent:: keyPressed (const KeyPress& key,
                 Component* originatingComponent)
{
//    DBG(key.getTextDescription());
//    DBG(key.getKeyCode());
    if (key.getModifiers().isCommandDown())
    {
        if (key.getKeyCode() == 63235)
        {
            audio.setPosition(audio.getPosition()+5.0);
            return true;
        }
        else if (key.getKeyCode() == 63234)
        {
            audio.setPosition(audio.getPosition()-5.0);
            return true;
        }
        return false;
    }
    return false;
}
void AudioFileTransportComponent::audioFileUpdated(int64 fileLength)
{
    transportSlider.setRange(0.0, fileLength);
}

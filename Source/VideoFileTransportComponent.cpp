//
//  VideoFileTransportComponent.cpp
//  AudioTranscriber
//
//  Created by Dominic Brown on 11/11/2017.
//
//

#include "VideoFileTransportComponent.h"

VideoFileTransportComponent::VideoFileTransportComponent()
{
    //File videoFile ("/Users/dc3-brown/Desktop/PhD/Work/Data/Experts/Chagall/Qualitative/2017-11-07/Chagall-observation-2017-11-07.MOV");
    
//    jassert(videoFile.existsAsFile());
    addAndMakeVisible(video);
}
VideoFileTransportComponent::~VideoFileTransportComponent()
{
}
void VideoFileTransportComponent::resized()
{
    auto area(getLocalBounds());
    
    video.setBounds(area);
    
}
void VideoFileTransportComponent:: sliderValueChanged (Slider* slider)
{
    
}
void VideoFileTransportComponent:: buttonClicked(Button* button)
{
    
}

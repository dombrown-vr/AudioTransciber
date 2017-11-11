//
//  VideoFileTransportComponent.h
//  AudioTranscriber
//
//  Created by Dominic Brown on 11/11/2017.
//
//

#ifndef __AudioTranscriber__VideoFileTransportComponent__
#define __AudioTranscriber__VideoFileTransportComponent__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"


class VideoFileTransportComponent
{
public:
    VideoFileTransportComponent();
    ~VideoFileTransportComponent();
    
private:
    VideoComponent video;
    Slider transportBar;

    
    
};

#endif /* defined(__AudioTranscriber__VideoFileTransportComponent__) */

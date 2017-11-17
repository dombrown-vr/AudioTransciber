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
#include "FileTransportComponent.h"

class VideoFileTransportComponent : public FileTransportComponent
{
public:
    VideoFileTransportComponent();
    ~VideoFileTransportComponent();
    
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    
    void buttonClicked (Button*) override;
    
    void setValueTree(ValueTree vt_) override {}
    
private:
    VideoComponent video;
    
};

#endif /* defined(__AudioTranscriber__VideoFileTransportComponent__) */

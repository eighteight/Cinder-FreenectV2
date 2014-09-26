//
//  ofRGBPacketProcessor.h
//
//  Created by Theodore Watson on 6/23/14.
//
//

#pragma once

//#include "ofImage.h"

#include "libfreenect2/rgb_packet_processor.h"
#include "libfreenect2/frame_listener.h"

namespace libfreenect2{

class CinderRGBPacketProcessor : public RgbPacketProcessor{

    public:
        CinderRGBPacketProcessor();
        ~CinderRGBPacketProcessor();
    
         void process(const libfreenect2::RgbPacket &packet);

    protected:
        void newFrame();
        Frame *frame;
        cinder::Surface pix;

};

};
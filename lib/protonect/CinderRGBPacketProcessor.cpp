//
//  ofRGBPacketProcessor.cpp
//
//  Created by Theodore Watson on 6/23/14.
//
//

#include "CinderRGBPacketProcessor.h"

namespace libfreenect2
{

CinderRGBPacketProcessor::CinderRGBPacketProcessor(){
    newFrame();
}

CinderRGBPacketProcessor::~CinderRGBPacketProcessor(){

}

void CinderRGBPacketProcessor::newFrame(){
    frame = new Frame(1920, 1080, 3);
}

void CinderRGBPacketProcessor::process(const libfreenect2::RgbPacket &packet){
//    ofBuffer tmp;
//    tmp.set( ( char * )packet.jpeg_buffer, (unsigned int)packet.jpeg_buffer_length);
    
    //if( ofLoadImage(pix, tmp) ){
        pix = cinder::Surface8u ( (uint8_t*)packet.jpeg_buffer, frame->width, frame->height, frame->height*frame->width*frame->bytes_per_pixel, cinder::SurfaceChannelOrder::RGBA);
      //memcpy(frame->data, pix.getPixels(), pix.size());
          //memcpy(frame->data, pix.getData(), pix.getSize());
    
      if(listener_->addNewFrame(Frame::Color, frame)){
        newFrame();
      }
    //}
}

};
/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2017, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "PCCHMAppVideoEncoder.h"
#include "PCCSystem.h"

#ifdef USE_HMAPP_VIDEO_CODEC

using namespace pcc;

template <typename T>
PCCHMAppVideoEncoder<T>::PCCHMAppVideoEncoder() {}
template <typename T>
PCCHMAppVideoEncoder<T>::~PCCHMAppVideoEncoder() {}

template <typename T>
void PCCHMAppVideoEncoder<T>::encode( PCCVideo<T, 3>&            videoSrc,
                                      PCCVideoEncoderParameters& params,
                                      PCCVideoBitstream&         bitstream,
                                      PCCVideo<T, 3>&            videoRec ) {
  const size_t      width      = videoSrc.getWidth();
  const size_t      height     = videoSrc.getHeight();
  const size_t      frameCount = videoSrc.getFrameCount();
  std::stringstream cmd;
  cmd << params.encoderPath_ << " -c " << params.encoderConfig_ << " --InputFile=" << params.srcYuvFileName_
      << " --InputBitDepth=" << params.inputBitDepth_
      << " --InputChromaFormat=" << ( params.use444CodecIo_ ? "444" : "420" )
      << " --OutputBitDepth=" << params.outputBitDepth_ << " --OutputBitDepthC=" << params.outputBitDepth_
      << " --FrameRate=30"
      << " --FrameSkip=0"
      << " --SourceWidth=" << width << " --SourceHeight=" << height << " --ConformanceWindowMode=1 "
      << " --FramesToBeEncoded=" << frameCount << " --BitstreamFile=" << params.binFileName_
      << " --ReconFile=" << params.recYuvFileName_ << " --QP=" << params.qp_;
  if ( params.internalBitDepth_ != 0 ) {
    cmd << " --InternalBitDepth=" << params.internalBitDepth_ << " --InternalBitDepthC=" << params.internalBitDepth_;
  }
  if ( params.usePccMotionEstimation_ ) {
    cmd << " --UsePccMotionEstimation=1"
        << " --BlockToPatchFile=" << params.blockToPatchFile_ << " --OccupancyMapFile=" << params.occupancyMapFile_
        << " --PatchInfoFile=" << params.patchInfoFile_;
  }
  if ( params.use444CodecIo_ ) { cmd << " --InputColourSpaceConvert=RGBtoGBR"; }
  std::cout << cmd.str() << std::endl;

  videoSrc.write( params.srcYuvFileName_, params.inputBitDepth_ == 8 ? 1 : 2 );
  if ( pcc::system( cmd.str().c_str() ) ) {
    std::cout << "Error: can't run system command!" << std::endl;
    exit( -1 );
  }
  PCCCOLORFORMAT format = getColorFormat( params.recYuvFileName_ );
  videoRec.clear();
  videoRec.read( params.recYuvFileName_, width, height, format, frameCount, params.outputBitDepth_ == 8 ? 1 : 2 );
  bitstream.read( params.binFileName_ );
}

template <typename T>
PCCCOLORFORMAT PCCHMAppVideoEncoder<T>::getColorFormat( std::string& name ) {
  if ( ( name.find( "_p444.rgb" ) ) != std::string::npos ) {
    return PCCCOLORFORMAT::RGB444;
  } else if ( ( name.find( "_p444.yuv" ) ) != std::string::npos ) {
    return PCCCOLORFORMAT::YUV444;
  } else if ( ( name.find( "_p420.yuv" ) ) != std::string::npos ) {
    return PCCCOLORFORMAT::YUV420;
  } else {
    printf( "PCCHMAppVideoEncoder can't find parameters %s \n", name.c_str() );
    exit( -1 );
  }
  return PCCCOLORFORMAT::UNKNOWN;
}

template class pcc::PCCHMAppVideoEncoder<uint8_t>;
template class pcc::PCCHMAppVideoEncoder<uint16_t>;

#endif  //~USE_HMAPP_VIDEO_CODEC
/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2017, ISO/IEC
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
 *  * Neither the name of the ISO/IEC nor the names of its contributors may
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
#ifndef PCC_BITSTREAM_BITSTREAM_ENCODER_H
#define PCC_BITSTREAM_BITSTREAM_ENCODER_H

#include "PCCBitstreamCommon.h"
#include <map>

namespace pcc {

class PCCBitstream;
class PCCHighLevelSyntax;
class ProfileTierLevel;
class V3CParameterSet;
class OccupancyInformation;
class GeometryInformation;
class AttributeInformation;
class AtlasTileHeader;
class AtlasTileDataUnit;
class PatchDataGroup;
class PatchDataGroupUnitPayload;
class PatchV3CParameterSet;
class PatchFrameGeometryParameterSet;
class PatchFrameAttributeParameterSet;
class GeometryPatchParameterSet;
class GeometryPatchParams;
class AttributePatchParameterSet;
class AttributePatchParams;
class GeometryFrameParams;
class PatchTileLayerUnit;
class PatchFrameParameterSet;
class PatchTileHeader;
class RefListStruct;
class PatchTileDataUnit;
class PatchInformationData;
class PatchDataUnit;
class InterPatchDataUnit;
class MergePatchDataUnit;
class SkipPatchDataUnit;
class RawPatchDataUnit;
class EOMPatchDataUnit;
class AttributeSequenceParams;
class AttributeFrameParams;
class PLRInformation;
class PLRData;
class SeiMessage;
class AtlasFrameTileInformation;
class SampleStreamNalUnit;
class NalUnit;
class AccessUnitDelimiterRbsp;
class EndOfSequenceRbsp;
class EndOfBitstreamRbsp;
class FillerDataRbsp;
class V3CUnit;
class VpsVpccExtension;
class AspsVpccExtension;
class AfpsVpccExtension;
class AtlasAdaptationParameterSetRbsp;
class AapsVpccExtension;
class AtlasCameraParameters;

class PCCBitstreamWriter {
 public:
  PCCBitstreamWriter();
  ~PCCBitstreamWriter();

  int32_t write( SampleStreamNalUnit& ssnu, PCCBitstream& bitstream );
  size_t  write( SampleStreamV3CUnit& ssvu, PCCBitstream& bitstream );
  int     encode( PCCHighLevelSyntax& syntax, SampleStreamV3CUnit& ssvu );

#ifdef BITSTREAM_TRACE
  void setTraceFile( FILE* traceFile ) { traceFile_ = traceFile; }
#endif
 private:
  // 7.3.2.1 General V3C unit syntax
  void v3cUnit( PCCHighLevelSyntax& syntax, PCCBitstream& bitstream, V3CUnitType V3CUnitType );

  // 7.3.2.2 V3C unit header syntax
  static void v3cUnitHeader( PCCHighLevelSyntax& syntax, PCCBitstream& bitstream, V3CUnitType V3CUnitType );

  // 7.3.2.4 V3C unit payload syntax
  void v3cUnitPayload( PCCHighLevelSyntax& syntax, PCCBitstream& bitstream, V3CUnitType V3CUnitType );

  static void videoSubStream( PCCHighLevelSyntax& syntax, PCCBitstream& bitstream, V3CUnitType V3CUnitType );

  // 7.3.3 Byte alignment syntax
  static void byteAlignment( PCCBitstream& bitstream );

  // 7.3.4.1 General Sequence parameter set syntax
  void v3cParameterSet( V3CParameterSet& vps, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.4.2 Profile, tier, and level
  static void profileTierLevel( ProfileTierLevel& ptl, PCCBitstream& bitstream );

  // 7.3.4.3 Occupancy parameter information syntax
  static void occupancyInformation( OccupancyInformation& oi, PCCBitstream& bitstream );

  // 7.3.4.4 Geometry information syntax
  static void geometryInformation( GeometryInformation& gi, V3CParameterSet& vps, PCCBitstream& bitstream );

  // 7.3.4.5 Attribute information syntax
  static void attributeInformation( AttributeInformation& ai, V3CParameterSet& sps, PCCBitstream& bitstream );

  // 7.3.4.6 Profile toolset constraints information syntax
  static void profileToolsetConstraintsInformation( ProfileToolsetConstraintsInformation& ptci,
                                                    PCCBitstream&                         bitstream );

  // 7.2 Specification of syntax functions and descriptors
  static bool byteAligned( PCCBitstream& bitstream );
  static bool moreDataInPayload( PCCBitstream& bitstream );
  static bool moreRbspData( PCCBitstream& bitstream );
  static bool moreRbspTrailingData( PCCBitstream& bitstream );
  static bool moreDataInV3CUnit( PCCBitstream& bitstream );
  static void rbspTrailingBits( PCCBitstream& bitstream );
  static bool payloadExtensionPresent( PCCBitstream& bitstream );

  // 7.3.5 NAL unit syntax
  // 7.3.5.1 General NAL unit syntax
  void nalUnit( PCCBitstream& bitstream, NalUnit& nalUnit );
  // 7.3.5.2 NAL unit header syntax
  static void nalUnitHeader( PCCBitstream& bitstream, NalUnit& nalUnit );

  // 7.3.5.2  NAL unit header syntax
  // 7.3.6.1 Atlas sequence parameter set Rbsp
  // 7.3.6.1.1 General Atlas sequence parameter set Rbsp
  void atlasSequenceParameterSetRbsp( AtlasSequenceParameterSetRbsp& asps,
                                      PCCHighLevelSyntax&            syntax,
                                      PCCBitstream&                  bitstream );
  // 7.3.6.1.2 Point local reconstruction information syntax
  static void plrInformation( AtlasSequenceParameterSetRbsp& asps,
                              PCCHighLevelSyntax&            syntax,
                              PCCBitstream&                  bitstream );

  // 7.3.6.2 Atlas frame parameter set Rbsp syntax
  // 7.3.6.2.1 General atlas frame parameter set Rbsp syntax
  void atlasFrameParameterSetRbsp( AtlasFrameParameterSetRbsp& afps,
                                   PCCHighLevelSyntax&         syntax,
                                   PCCBitstream&               bitstream );

  // 7.3.6.2.2 Atlas frame tile information syntax
  static void atlasFrameTileInformation( AtlasFrameTileInformation&     afti,
                                         AtlasSequenceParameterSetRbsp& asps,
                                         PCCBitstream&                  bitstream );

  // 7.3.6.2 Atlas adaptation parameter set RBSP syntax
  // 7.3.6.2.1 General atlas adaptation parameter set RBSP syntax
  void atlasAdaptationParameterSetRbsp( AtlasAdaptationParameterSetRbsp& aaps, PCCBitstream& bitstream );

  // 7.3.6.4  Supplemental enhancement information Rbsp
  void seiRbsp( PCCHighLevelSyntax& syntax, PCCBitstream& bitstream, SEI& sei, NalUnitType nalUnitType );

  // 7.3.6.6  Access unit delimiter Rbsp syntax
  void auDelimiterRbsp( AccessUnitDelimiterRbsp& audrbsp, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );
  // 7.3.6.7  End of sequence Rbsp syntax
  void endOfSequenceRbsp( EndOfSequenceRbsp& eosbsp, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );
  // 7.3.6.8  End of bitstream Rbsp syntax
  void endOfBitstreamRbsp( EndOfBitstreamRbsp& eobrbsp, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );
  // 7.3.6.9  Filler data Rbsp syntax
  void fillerDataRbsp( FillerDataRbsp& fdrbsp, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.6.9 Atlas tile group layer Rbsp syntax = patchTileLayerUnit
  void atlasTileLayerRbsp( AtlasTileLayerRbsp& atgl, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.6.11  Atlas tile group header syntax
  void atlasTileHeader( AtlasTileHeader& ath, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.6.12  Reference list structure syntax
  static void refListStruct( RefListStruct& rls, AtlasSequenceParameterSetRbsp& asps, PCCBitstream& bitstream );
  // 7.3.7.1  General atlas tile group data unit syntax =patchTileDataUnit
  void atlasTileDataUnit( AtlasTileDataUnit&  atdu,
                          AtlasTileHeader&    ath,
                          PCCHighLevelSyntax& syntax,
                          PCCBitstream&       bitstream );

  // 7.3.7.2  Patch information data syntax
  void patchInformationData( PatchInformationData& pid,
                             size_t                patchMode,
                             AtlasTileHeader&      ath,
                             PCCHighLevelSyntax&   syntax,
                             PCCBitstream&         bitstream );

  // 7.3.7.3  Patch data unit syntax : AtlasTileHeader instead of
  // PatchTileHeader
  void patchDataUnit( PatchDataUnit& pdu, AtlasTileHeader& ath, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.7.4  Skip patch data unit syntax
  static void skipPatchDataUnit( PCCBitstream& bitstream );

  // 7.3.7.5  Merge patch data unit syntax
  void mergePatchDataUnit( MergePatchDataUnit& mpdu,
                           AtlasTileHeader&    ath,
                           PCCHighLevelSyntax& syntax,
                           PCCBitstream&       bitstream );

  // 7.3.7.6  Inter patch data unit syntax
  void interPatchDataUnit( InterPatchDataUnit& ipdu,
                           AtlasTileHeader&    ath,
                           PCCHighLevelSyntax& syntax,
                           PCCBitstream&       bitstream );

  // 7.3.7.7  Raw patch data unit syntax
  static void rawPatchDataUnit( RawPatchDataUnit&   rpdu,
                                AtlasTileHeader&    ath,
                                PCCHighLevelSyntax& syntax,
                                PCCBitstream&       bitstream );
  // 7.3.7.8  EOM patch data unit syntax
  static void eomPatchDataUnit( EOMPatchDataUnit&   epdu,
                                AtlasTileHeader&    ptgh,
                                PCCHighLevelSyntax& syntax,
                                PCCBitstream&       bitstream );

  // 7.3.7.9  Point local reconstruction data syntax
  static void plrData( PLRData&                       plrd,
                       PCCHighLevelSyntax&            syntax,
                       AtlasSequenceParameterSetRbsp& asps,
                       PCCBitstream&                  bitstream );

  // 7.3.8 Supplemental enhancement information message syntax
  void seiMessage( PCCBitstream& bitstream, PCCHighLevelSyntax& syntax, SEI& sei, NalUnitType nalUnitType );

  // 7.3.5.1 General patch data group unit syntax
  void atlasSubStream( PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.5.3 Patch sequence parameter set syntax
  void patchV3CParameterSet( PatchDataGroup& pdg, size_t index, PCCBitstream& bitstream );

  // 7.3.5.4 Patch frame geometry parameter set syntax
  void patchFrameGeometryParameterSet( PatchDataGroup&  pdg,
                                       size_t           index,
                                       V3CParameterSet& v3cParameterSet,
                                       PCCBitstream&    bitstream );

  // 7.3.5.5 Geometry frame Params syntax
  void geometryFrameParams( GeometryFrameParams& geometryFrameParams, PCCBitstream& bitstream );

  // 7.3.5.6 Patch frame attribute parameter set syntax
  void patchFrameAttributeParameterSet( PatchDataGroup&  pdg,
                                        size_t           index,
                                        V3CParameterSet& v3cParameterSet,
                                        PCCBitstream&    bitstream );

  // 7.3.5.7 Attribute frame Params syntax
  void attributeFrameParams( AttributeFrameParams& attributeFrameParams, size_t dimension, PCCBitstream& bitstream );

  // 7.3.5.8 Geometry patch parameter set syntax
  void geometryPatchParameterSet( PatchDataGroup& atlasSubStream, size_t index, PCCBitstream& bitstream );

  // 7.3.5.9 Geometry patch Params syntax
  void geometryPatchParams( GeometryPatchParams&            geometryPatchParams,
                            PatchFrameGeometryParameterSet& patchFrameGeometryParameterSet,
                            PCCBitstream&                   bitstream );

  // 7.3.5.10 Attribute patch parameter set syntax
  void attributePatchParameterSet( PatchDataGroup&  pdg,
                                   size_t           index,
                                   V3CParameterSet& v3cParameterSet,
                                   PCCBitstream&    bitstream );

  // 7.3.5.11 Attribute patch Params syntax
  void attributePatchParams( AttributePatchParams&            attributePatchParams,
                             PatchFrameAttributeParameterSet& afps,
                             size_t                           dimension,
                             PCCBitstream&                    bitstream );

  // 7.3.5.12 Patch frame parameter set syntax
  void patchFrameParameterSet( PatchDataGroup&  pdg,
                               size_t           index,
                               V3CParameterSet& v3cParameterSet,
                               PCCBitstream&    bitstream );

  // 7.3.5.13 Patch frame layer unit syntax
  void patchTileLayerUnit( PatchDataGroup& pdg, size_t index, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.5.14 Patch frame header syntax
  void patchTileHeader( PatchTileHeader&    patchTileHeader,
                        PatchTileHeader&    pfhPrev,
                        PCCHighLevelSyntax& syntax,
                        PCCBitstream&       bitstream );

  // 7.3.5.15 Reference list structure syntax
  void refListStruct( RefListStruct&        refListStruct,
                      PatchV3CParameterSet& patchV3CParameterSet,
                      PCCBitstream&         bitstream );

  // 7.3.5.16 Patch frame data unit syntax
  void patchTileDataUnit( PatchTileDataUnit&  ptgdu,
                          PatchTileHeader&    patchTileHeader,
                          PCCHighLevelSyntax& syntax,
                          PCCBitstream&       bitstream );

  // 7.3.5.17 Patch information data syntax
  void patchInformationData( PatchInformationData& pid,
                             size_t                patchIndex,
                             size_t                patchMode,
                             PatchTileHeader&      ptgh,
                             PCCHighLevelSyntax&   syntax,
                             PCCBitstream&         bitstream );

  // 7.3.5.18 Patch data unit syntax
  void patchDataUnit( PatchDataUnit& pdu, PatchTileHeader& ptgh, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // 7.3.5.19  Delta Patch data unit
  void deltaPatchDataUnit( InterPatchDataUnit& dpdu,
                           PatchTileHeader&    ptgh,
                           PCCHighLevelSyntax& syntax,
                           PCCBitstream&       bitstream );

  // 7.3.5.20 raw patch data unit syntax
  void pcmPatchDataUnit( RawPatchDataUnit&   rpdu,
                         PatchTileHeader&    ptgh,
                         PCCHighLevelSyntax& syntax,
                         PCCBitstream&       bitstream );

  // 7.3.5.x EOM patch data unit syntax
  void eomPatchDataUnit( EOMPatchDataUnit&   epdu,
                         PatchTileHeader&    ptgh,
                         PCCHighLevelSyntax& syntax,
                         PCCBitstream&       bitstream );

  // 7.3.5.22 Supplemental enhancement information message syntax
  void seiMessage( PatchDataGroup& pdg, size_t index, PCCHighLevelSyntax& syntax, PCCBitstream& bitstream );

  // B.2 Sample stream V3C unit syntax and semantics
  // B.2.1 Sample stream V3C header syntax
  static void sampleStreamV3CHeader( PCCBitstream& bitstream, SampleStreamV3CUnit& ssvu );

  // B.2.2 Sample stream NAL unit syntax
  static void sampleStreamV3CUnit( PCCBitstream& bitstream, SampleStreamV3CUnit& ssvu, V3CUnit& v3cUnit );

  // C.2 Sample stream NAL unit syntax and semantics
  // C.2.1 Sample stream NAL header syntax
  static void sampleStreamNalHeader( PCCBitstream& bitstream, SampleStreamNalUnit& ssnu );
  // C.2.2 Sample stream NAL unit syntax
  void sampleStreamNalUnit( PCCHighLevelSyntax&  syntax,
                            PCCBitstream&        bitstream,
                            SampleStreamNalUnit& ssnu,
                            NalUnit&             nalUnit,
                            size_t               index = 0 );

  // F.2  SEI payload syntax
  // F.2.1  General SEI message syntax
  void seiPayload( PCCBitstream& bitstream, PCCHighLevelSyntax& syntax, SEI& sei, NalUnitType nalUnitType );

  // F.2.2  Filler payload SEI message syntax
  static void fillerPayload( PCCBitstream& bitstream, SEI& sei );
  // F.2.3  User data registered by Recommendation ITU-T T.35 SEI message syntax
  static void userDataRegisteredItuTT35( PCCBitstream& bitstream, SEI& sei );
  // F.2.4  User data unregistered SEI message syntax
  static void userDataUnregistered( PCCBitstream& bitstream, SEI& sei );
  // F.2.5  Recovery point SEI message syntax
  static void recoveryPoint( PCCBitstream& bitstream, SEI& sei );
  // F.2.6  No display SEI message syntax
  static void noDisplay( PCCBitstream& bitstream, SEI& sei );
  // F.2.7  Reserved SEI message syntax
  static void reservedSeiMessage( PCCBitstream& bitstream, SEI& sei );
  // F.2.8  SEI manifest SEI message syntax
  static void seiManifest( PCCBitstream& bitstream, SEI& sei );
  // F.2.9  SEI prefix indication SEI message syntax
  static void seiPrefixIndication( PCCBitstream& bitstream, SEI& sei );
  // F.2.10  Attribute transformation parameters SEI message syntax
  static void attributeTransformationParams( PCCBitstream& bitstream, SEI& sei );
  // F.2.11  Active substreams SEI message syntax
  static void activeSubBitstreams( PCCBitstream& bitstream, SEI& sei );
  // F.2.12  Component codec mapping SEI message syntax
  static void componentCodecMapping( PCCBitstream& bitstream, SEI& sei );
  // F.2.14  Volumetric Tiling SEI message syntax

  // F.2.15  Buffering period SEI message syntax
  static void bufferingPeriod( PCCBitstream&        bitstream,
                               SEI&                 sei,
                               bool                 NalHrdBpPresentFlag,
                               bool                 AclHrdBpPresentFlag,
                               std::vector<uint8_t> hrdCabCntMinus1 );
  // F.2.16  Atlas frame timing SEI message syntax
  static void atlasFrameTiming( PCCBitstream& bitstream, SEI& sei, bool CabDabDelaysPresentFlag );

  // F.2.13.1 Scene object information SEI message syntax
  static void sceneObjectInformation( PCCBitstream& bitstream, SEI& sei );
  // F.2.13.2 Object label information SEI message syntax
  static void objectLabelInformation( PCCBitstream& bitstream, SEI& sei );
  // F.2.13.3 Patch information SEI message syntax
  static void patchInformation( PCCBitstream& bitstream, SEI& sei );
  // F.2.13.4 Volumetric rectangle information SEI message syntax
  static void volumetricRectangleInformation( PCCBitstream& bitstream, SEI& sei );
  // F.2.13.5  Atlas information  SEI message syntax
  static void atlasInformation( PCCBitstream& bitstream, SEI& seiAbstract );
  // F.2.16.1 Viewport camera parameters SEI messages syntax
  static void viewportCameraParameters( PCCBitstream& bitstream, SEI& seiAbstract );
  // F.2.16.2	Viewport position SEI messages syntax
  static void viewportPosition( PCCBitstream& bitstream, SEI& seiAbstract );
  // F.2.17 Decoded Atlas Information Hash SEI message syntax
  static void decodedAtlasInformationHash( PCCBitstream& bitstream, SEI& seiAbstract );
  // H.16.2.1	Occupancy synthesis SEI message syntax
  static void occupancySynthesis( PCCBitstream& bitstream, SEI& seiAbstract );
  // H.16.2.2 Geometry smoothing SEI message syntax
  static void geometrySmoothing( PCCBitstream& bitstream, SEI& seiAbstract );
  // H.16.2.3 Attribute smoothing SEI message syntax
  static void attributeSmoothing( PCCBitstream& bitstream, SEI& seiAbstract );

  // G.2  VUI syntax
  // G.2.1  VUI parameters syntax
  void vuiParameters( PCCBitstream& bitstream, VUIParameters& vp );
  // G.2.2  HRD parameters syntax
  void hrdParameters( PCCBitstream& bitstream, HrdParameters& hp );
  // G.2.3  Sub-layer HRD parameters syntax
  static void hrdSubLayerParameters( PCCBitstream& bitstream, HrdSubLayerParameters& hlsp, size_t cabCnt );
  // G.2.4	Coordinate system parameters syntax
  static void coordinateSystemParameters( PCCBitstream& bitstream, CoordinateSystemParameters& csp );

  // H.7.3.4.1 VPS V-PCC extension syntax
  static void vpsVpccExtension( PCCBitstream& bitstream, VpsVpccExtension& ext );

  // H.7.3.4.2 VPS MIV extension syntax
  static void vpsMivExtension( PCCBitstream& bitstream );

  // H.7.3.6.1.1 ASPS V-PCC extension syntax
  static void aspsVpccExtension( PCCBitstream& bitstream, AtlasSequenceParameterSetRbsp& asps, AspsVpccExtension& ext );
  // H.7.3.6.1.2 ASPS MIV extension syntax
  static void aspsMivExtension( PCCBitstream& bitstream );

  // H.7.3.6.2.1 AFPS V-PCC extension syntax
  static void afpsVpccExtension( PCCBitstream& bitstream, AfpsVpccExtension& ext );
  // H.7.3.6.2.2 AFPS MIV extension syntax
  static void afpsMivExtension( PCCBitstream& bitstream );

  // H.7.3.6.2.1 AAPS V-PCC extension syntax
  static void aapsVpccExtension( PCCBitstream& bitstream, AapsVpccExtension& ext );
  // H.7.3.6.2.2 AAPS MIV extension syntax
  static void aapsMivExtension( PCCBitstream& bitstream );

  // H.7.3.6.2.2 Atlas camera parameters syntax
  static void atlasCameraParameters( PCCBitstream& bitstream, AtlasCameraParameters& acp );

// PCCEncoderParameters params_;
#ifdef BITSTREAM_TRACE
  FILE* traceFile_;
#endif
};

};  // namespace pcc

#endif /* PCC_BITSTREAM_BITSTREAM_ENCODER_H */

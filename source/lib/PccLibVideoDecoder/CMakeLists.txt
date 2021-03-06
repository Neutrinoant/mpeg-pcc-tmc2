CMAKE_MINIMUM_REQUIRED (VERSION 2.8.11)

GET_FILENAME_COMPONENT(MYNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
STRING(REPLACE " " "_" MYNAME ${MYNAME})
PROJECT(${MYNAME} C CXX)

FILE(GLOB SRC  include/*.h 
               source/*.cpp  
               ${HM_LIB_SOURCE_DIR}/TAppCommon/* )

INCLUDE_DIRECTORIES( include 
                     ${CMAKE_SOURCE_DIR}/source/lib/PccLibCommon/include/
                     ${CMAKE_SOURCE_DIR}/source/lib/PccLibBitstreamCommon/include/
                     ${HM_LIB_SOURCE_DIR}/TAppCommon/
                     ${HM_LIB_SOURCE_DIR}/ )

SET( LIBS PccLibCommon )
IF( USE_HMLIB_VIDEO_CODEC )
    SET( LIBS ${LIBS} TLibCommon TLibVideoIO TLibDecoder )
ENDIF()
IF( USE_FFMPEG_VIDEO_CODEC )  
  INCLUDE_DIRECTORIES(${FFMPEG_INCLUDE} )
  IF( WIN32 OR MSVC OR MSYS OR MINGW )
    LINK_DIRECTORIES( ${FFMPEG_DEV_DIR}/lib ) 
  ENDIF()  
  SET( LIBS ${LIBS} ${AVCODEC_LIBRARY} ${AVUTIL_LIBRARY} ${AVFORMAT_LIBRARY} )
ENDIF()
IF( USE_HMAPP_VIDEO_CODEC )
  INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/dependencies/PccLibHevcParser/include )
  SET( LIBS ${LIBS} PccLibHevcParser )
ENDIF()
IF( USE_JMAPP_VIDEO_CODEC )
  INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/dependencies/PccLibAvcParser/include )
  SET( LIBS ${LIBS} PccLibAvcParser )
ENDIF()

ADD_LIBRARY( ${MYNAME} ${LINKER} ${SRC} )

TARGET_LINK_LIBRARIES( ${MYNAME} ${LIBS} )

SET_TARGET_PROPERTIES( ${MYNAME} PROPERTIES LINKER_LANGUAGE CXX)

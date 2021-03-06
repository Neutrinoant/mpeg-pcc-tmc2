cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

  
SET( HDRTOOLS_DIR             ${CMAKE_SOURCE_DIR}/dependencies/HDRTools )
MESSAGE("Clone and build HDRTools libraries: ${HDRTOOLS_DIR}") 

IF( NOT EXISTS "${HDRTOOLS_DIR}/CMakeLists.txt" )   
  EXECUTE_PROCESS( COMMAND git clone http://gitlab.com/standards/HDRTools.git ${HDRTOOLS_DIR} )  
ENDIF()

MESSAGE("HDRTOOLS_DIR       : ${HDRTOOLS_DIR}") 
IF ( NOT EXISTS "${HDRTOOLS_DIR}/common/CMakeLists.txt" )
  message( "\n\n Error: commande: \n \t  git clone http://gitlab.com/standards/HDRTools.git ${HDRTOOLS_DIR} not work")
  message( FATAL_ERROR "${HDRTOOLS_DIR}/common/CMakeLists.txt not exist")

ELSE()
  ADD_SUBDIRECTORY( ${HDRTOOLS_DIR}/common ) 
ENDIF()
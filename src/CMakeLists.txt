######################################################################################
### 1) Set all needed source files for the project
######################################################################################

FILE(GLOB SOURCES *.cpp)
SET(SAMPLE_SRCS ${SOURCES} PARENT_SCOPE)

SET(SAMPLE_MOC_HDRS
  ${CMAKE_CURRENT_SOURCE_DIR}/MoviePlayer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/MyCameraWindow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/MyMovieWindow.h
  PARENT_SCOPE
  )

######################################################################################


######################################################################################
### 2) Now where we go ?!?
######################################################################################

ADD_SUBDIRECTORY(audio_codec)
ADD_SUBDIRECTORY(video_codec)
ADD_SUBDIRECTORY(qopencv)

######################################################################################

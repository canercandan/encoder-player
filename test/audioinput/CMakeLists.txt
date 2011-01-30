######################################################################################
### 1) Set the application properties
######################################################################################

# Checks cmake version compatibility
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(audioinput)

######################################################################################


######################################################################################
### 2) Include useful features
######################################################################################

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtMultimedia REQUIRED)
INCLUDE(${QT_USE_FILE})

######################################################################################


######################################################################################
### 3) Set compiler definitions
######################################################################################

IF(UNIX)
  # enable warnings
  ADD_DEFINITIONS( -Wall -W -Wextra )
  # ADD_DEFINITIONS( -Weffc++)
  # ADD_DEFINITIONS( -g3 )
ENDIF()

######################################################################################


######################################################################################
### 4) Some routines for Qt resources
######################################################################################

# Here is an explaination to how to use qt4_wrap_cpp:
# http://www.mail-archive.com/cmake@cmake.org/msg18900.html

SET(SAMPLE_MOC_HDRS
  ${CMAKE_CURRENT_SOURCE_DIR}/audioinput.h
  ${CMAKE_CURRENT_SOURCE_DIR}/renderarea.h
  ${CMAKE_CURRENT_SOURCE_DIR}/inputtest.h
  )

#QT4_WRAP_UI(SAMPLE_UIS_SRCS ${SAMPLE_UIS})
QT4_WRAP_CPP(SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})
#QT4_ADD_RESOURCES(SAMPLE_RC_SRCS ${SAMPLE_RCS})
#QT4_ADD_TRANSLATION(SAMPLE_TRANS_SRCS ${SAMPLE_TRANS})

# Further details about translation below:
# http://www.cmake.org/Wiki/CMake:How_To_Build_Qt4_Software

######################################################################################


######################################################################################
### 5) Configure target of executable
######################################################################################

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

LINK_DIRECTORIES(
  ${MYPLAYER_BIN_DIR}/lib
  )

FILE(GLOB SOURCES *.cpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES} ${SAMPLE_MOC_SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES})

######################################################################################

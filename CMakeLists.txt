######################################################################################
### 1) Set the application properties
######################################################################################

# Checks cmake version compatibility
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(epitivo)

SET(PROJECT_VERSION_MAJOR 1)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 0)
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

######################################################################################


######################################################################################
### 2) Prepare some useful variables
######################################################################################

SET(EPITIVO_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SET(EPITIVO_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")

######################################################################################


######################################################################################
### 3) Include useful features
######################################################################################

INCLUDE(FindDoxygen)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtNetwork QtXml QtMultimedia REQUIRED)
INCLUDE(${QT_USE_FILE})

IF (UNIX)
  FIND_PACKAGE(PkgConfig)
  PKG_CHECK_MODULES(OpenCV opencv)

  SET(X_OPENCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS})
  SET(X_OPENCV_LIBRARY_DIRS ${OpenCV_LIBRARY_DIRS})
  SET(X_OPENCV_LIBRARIES ${OpenCV_LIBRARIES})
ELSE()
  FIND_PACKAGE(OpenCV REQUIRED)

  SET(X_OPENCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIR})
  SET(X_OPENCV_LIBRARY_DIRS ${OpenCV_DIR}/lib)
  SET(X_OPENCV_LIBRARIES ${OpenCV_LIBS})
ENDIF()

######################################################################################


######################################################################################
### 4) Include header files and library path
######################################################################################

INCLUDE_DIRECTORIES(
  ${X_OPENCV_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_BINARY_DIR}
  )

LINK_DIRECTORIES(
  ${X_OPENCV_LIBRARY_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}/lib
  )

######################################################################################


######################################################################################
### 5) Set compiler definitions
######################################################################################

IF (UNIX)
  # enable warnings
  ADD_DEFINITIONS( -Wall -W -Wextra )
  # ADD_DEFINITIONS( -Weffc++)
  ADD_DEFINITIONS( -g )
ENDIF()

######################################################################################


######################################################################################
### 6) Prepare some variables for CMAKE usage
######################################################################################

SET(SAMPLE_SRCS)
SET(SAMPLE_UIS)
SET(SAMPLE_MOC_HDRS)
SET(SAMPLE_RCS)
SET(SAMPLE_TRANS)

######################################################################################


######################################################################################
### 7) Now where we go ?
######################################################################################

#ADD_SUBDIRECTORY(resources)
#ADD_SUBDIRECTORY(forms)
ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(config)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(doc)

######################################################################################


######################################################################################
### 8) Some routines for Qt resources
######################################################################################

# Here is an explaination to how to use qt4_wrap_cpp:
# http://www.mail-archive.com/cmake@cmake.org/msg18900.html

# QT4_WRAP_UI(SAMPLE_UIS_SRCS ${SAMPLE_UIS})
# QT4_WRAP_CPP(SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})
# QT4_ADD_RESOURCES(SAMPLE_RC_SRCS ${SAMPLE_RCS})
# QT4_ADD_TRANSLATION(SAMPLE_TRANS_SRCS ${SAMPLE_TRANS})

# Further details about translation below:
# http://www.cmake.org/Wiki/CMake:How_To_Build_Qt4_Software

######################################################################################


######################################################################################
### 9) Create executable, link libraries and prepare target
######################################################################################

ADD_EXECUTABLE(
  ${PROJECT_NAME}
  ${SAMPLE_SRCS}
  ${SAMPLE_UIS_SRCS}
  ${SAMPLE_MOC_SRCS}
  ${SAMPLE_RC_SRCS}
  ${SAMPLE_TRANS_SRCS}
  )

SET(EPITIVO_LIBS video_codec audio_codec qopencv)

TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME}
  ${X_OPENCV_LIBRARIES}
  ${QT_LIBRARIES}
  ${EPITIVO_LIBS}
  )

INSTALL(
  TARGETS ${PROJECT_NAME}
  RUNTIME
  DESTINATION bin
  COMPONENT applications
  )

######################################################################################


######################################################################################
### 10) Include packaging
######################################################################################

INCLUDE(Packaging.cmake)

######################################################################################

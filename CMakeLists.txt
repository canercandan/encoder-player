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

ENABLE_LANGUAGE(CXX)
ENABLE_LANGUAGE(C)

######################################################################################


######################################################################################
### 3) Include useful features
######################################################################################

INCLUDE(FindDoxygen)

IF (UNIX)
  FIND_PACKAGE(PkgConfig)
  PKG_CHECK_MODULES(OpenCV opencv)
ELSE()
  FIND_PACKAGE(OpenCV REQUIRED)
ENDIF()

######################################################################################


######################################################################################
### 6) Now where we go ?
######################################################################################

ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(doc)
#ADD_SUBDIRECTORY(test)
#ADD_SUBDIRECTORY(application)

######################################################################################


######################################################################################
### 7) Include packaging
######################################################################################

INCLUDE(Packaging.cmake)

######################################################################################

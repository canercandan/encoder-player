######################################################################################
### 1) Check dependencies
######################################################################################

IF (NOT DEFINED PROJECT_NAME OR
    NOT DEFINED PROJECT_VERSION_MAJOR OR
    NOT DEFINED PROJECT_VERSION_MINOR OR
    NOT DEFINED PROJECT_VERSION_PATCH OR
    NOT DEFINED PROJECT_VERSION)
  MESSAGE(FATAL_ERROR "Be sure you have defined PROJECT_NAME and PROJECT_VERSION*.")
ENDIF()

######################################################################################


######################################################################################
### 2) Set up components
######################################################################################

SET(CPACK_COMPONENTS_ALL applications)
SET(CPACK_ALL_INSTALL_TYPES Full)

SET(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Epitivo")
SET(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION "Description")
SET(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")
SET(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

######################################################################################


######################################################################################
### 3) Set up general information about packaging
######################################################################################

# For more details: http://www.cmake.org/Wiki/CMake:Component_Install_With_CPack

#cpack package information
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_PACKAGE_DESCRIPTION "Epitivo is a classical video and audio encorder and decoder engine.")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Epitivo - the best software never seen before.")
SET(CPACK_PACKAGE_VENDOR "Epitech")
SET(CPACK_PACKAGE_CONTACT "caner@candan.fr")
SET(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
SET(CPACK_STRIP_FILES ${PROJECT_NAME})
SET(CPACK_SOURCE_STRIP_FILES "bin/${PROJECT_NAME}")
SET(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

######################################################################################


######################################################################################
### 3) Set up debian packaging information
######################################################################################

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqtgui4, libqt4-xml, libqt4-network, libqt4-core, libstdc++6, libgcc1, libc6, libcv4, libhighgui4, libcvaux4")

SET(CPACK_DEBIAN_PACKAGE_SECTION "video")
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

######################################################################################


######################################################################################
### 3) And finally, include cpack, this is the last thing to do.
######################################################################################

INCLUDE(CPack)

######################################################################################

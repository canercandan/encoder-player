#######################################################################################
### Doc generation using Doxygen
#######################################################################################

IF (DOXYGEN_FOUND)
  SET(DOC_DIR ${CMAKE_CURRENT_BINARY_DIR} CACHE PATH "Documentation directory")
  SET(DOC_CONFIG_FILE "doxyfile" CACHE PATH "Documentation configuration file")
  # define the doc target
  IF (DOXYGEN_EXECUTABLE)
    ADD_CUSTOM_TARGET(doc
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOC_CONFIG_FILE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      )
  ENDIF (DOXYGEN_EXECUTABLE)

  # configure doxyfile file
  CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/${DOC_CONFIG_FILE}.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${DOC_CONFIG_FILE}")
ELSE (DOXYGEN_FOUND)
  MESSAGE(STATUS "Unable to generate the documentation, Doxygen package not found")
ENDIF (DOXYGEN_FOUND)

#######################################################################################

# Generate ROCSConfig.cmake
set(WARNING "\n# This file was automatically generated from FindROCS.cmake.\n# DO NOT MODIFY!\n# ")
configure_file(${ROCS_SRC_CMAKE}/FindROCS.cmake ${CMAKE_BINARY_DIR}/cmake/ROCSConfig.cmake ESCAPE_QUOTES @ONLY)

# Install ROCSConfig.cmake
install(FILES ${CMAKE_BINARY_DIR}/cmake/ROCSConfig.cmake DESTINATION .)

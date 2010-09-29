# Check for Doxygen
find_package(Doxygen)

if (DOXYGEN_FOUND)

	# Prepare list of paths for Doxygen
	set(ROCS_DOXYGEN_DOX_PATHS "${ROCS_SRC_DOC}/dox ${ROCS_SRC_TEST}/dox")
	set(ROCS_DOXYGEN_IMAGE_PATHS "${ROCS_SRC_DOC}/dox ${ROCS_SRC_TEST}/dox")
	set(ROCS_DOXYGEN_CODE_PATHS_CPP "")
	set(ROCS_DOXYGEN_CODE_PATHS_JAVA "")
	set(ROCS_DOXYGEN_CODE_PATHS_PYTHON "")
	foreach(M ${ROCS_MODULE_LIST})
		set(ROCS_DOXYGEN_DOX_PATHS " ${ROCS_DOXYGEN_DOX_PATHS} ${ROCS_SRC_MODULES}/${M}/dox")
		set(ROCS_DOXYGEN_IMAGE_PATHS " ${ROCS_DOXYGEN_IMAGE_PATHS} ${ROCS_SRC_MODULES}/${M}/dox")
		set(ROCS_DOXYGEN_CODE_PATHS_CPP " ${ROCS_DOXYGEN_CODE_PATHS} ${ROCS_SRC_MODULES}/${M}/cpp")
		set(ROCS_DOXYGEN_CODE_PATHS_JAVA " ${ROCS_DOXYGEN_CODE_PATHS} ${ROCS_SRC_MODULES}/${M}/java")
		set(ROCS_DOXYGEN_CODE_PATHS_PYTHON " ${ROCS_DOXYGEN_CODE_PATHS} ${ROCS_SRC_MODULES}/${M}/python")
	endforeach(M)

	# Update doxygen files
	configure_file(Doxyfile_cpp.in ${CMAKE_BINARY_DIR}/doc/Doxyfile_cpp ESCAPE_QUOTES @ONLY)
	configure_file(Doxyfile_java.in ${CMAKE_BINARY_DIR}/doc/Doxyfile_java ESCAPE_QUOTES @ONLY)
	configure_file(Doxyfile_python.in ${CMAKE_BINARY_DIR}/doc/Doxyfile_python ESCAPE_QUOTES @ONLY)

	# Generate targts
	add_custom_target(doc_cpp ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doc/Doxyfile_cpp WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc COMMENT "Building C++ documentation")
	add_custom_target(doc_java ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doc/Doxyfile_java WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc COMMENT "Building Java documentation")
	add_custom_target(doc_python ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doc/Doxyfile_python WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc COMMENT "Building Python documentation")

	# Install documentation
	install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html_cpp/ DESTINATION ${ROCS_DIR}/doc/html_cpp)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html_java/ DESTINATION ${ROCS_DIR}/doc/html_java)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html_python/ DESTINATION ${ROCS_DIR}/doc/html_python)
	install(FILES ${ROCS_SRC_ROOT}/README.md ${ROCS_SRC_ROOT}/LICENSE.md DESTINATION ${ROCS_DIR}/doc)
	if (NOT ${INSTALL_TO_SRC_ROOT})
		install(FILES ${ROCS_SRC_DOC}/INSTALL.md ${ROCS_SRC_DOC}/CHANGELOG.md DESTINATION ${ROCS_DIR}/doc)
	endif (NOT ${INSTALL_TO_SRC_ROOT})

else (DOXYGEN_FOUND)
	message(FATAL_ERROR "Doxygen not found. Documentation will not be generated.")
endif (DOXYGEN_FOUND)



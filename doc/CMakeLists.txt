# Check for Doxygen
find_package(Doxygen)

if (DOXYGEN_FOUND)
	# Get list of paths to modules
	set(ROCS_DOC_PATHS "${ROCS_SRC_DOC}/dox ${ROCS_SRC_APPS}/doc ${ROCS_SRC_TEST}/doc ${ROCS_SRC_THIRDPARTY}/doc")
	
	# set(ROCS_DOC_IMAGE_PATHS "${ROCS_SRC_DOC}/images ${ROCS_SRC_APPS}/doc/images ${ROCS_SRC_TEST}/doc/images ${ROCS_SRC_THIRDPARTY}/doc/images")
	
	foreach(M ${ROCS_MODULE_LIST})
		### paths with the 'python' folder : 
		# set(ROCS_DOC_PATHS " ${ROCS_DOC_PATHS} ${ROCS_SRC_MODULES}/${M}/doc ${ROCS_SRC_MODULES}/${M}/cpp/${M} ${ROCS_SRC_MODULES}/${M}/python/${M}")
		### paths without the 'python' folder :
		set(ROCS_DOC_PATHS " ${ROCS_DOC_PATHS} ${ROCS_SRC_MODULES}/${M}/doc ${ROCS_SRC_MODULES}/${M}/cpp/${M}")
		
		### images path
		# set(ROCS_DOC_IMAGE_PATHS " ${ROCS_DOC_IMAGE_PATHS} ${ROCS_SRC_MODULES}/${M}/doc/images")
	endforeach(M)

	# Update doxygen files
	configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/doc/Doxyfile ESCAPE_QUOTES @ONLY)

	# Generate targts
	add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doc/Doxyfile WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc COMMENT "Building documentation")
	install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html/ DESTINATION ${ROCS_DIR}/doc/html)
	install(FILES ${ROCS_SRC_ROOT}/AUTHORS ${ROCS_SRC_ROOT}/LICENSE ${ROCS_SRC_ROOT}/README DESTINATION ${ROCS_DIR}/doc)
else (DOXYGEN_FOUND)
	message(FATAL_ERROR "Doxygen not found. Documentation will not be generated.")
endif (DOXYGEN_FOUND)



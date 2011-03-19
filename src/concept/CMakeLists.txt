if(ROCS_BUILD_MODULE_CONCEPT)

	# Module
	add_rocs_cpp_module(concept
		SOURCES Graph.cc Query.cc
		HEADERS Graph.h Query.h
		LINK_MODULES core
		LINK dai)

	# Remove deprecated includes messages
	set_property(TARGET rocs_concept PROPERTY COMPILE_FLAGS "-Wno-deprecated")

	# Tests
	add_rocs_cpp_test_suite(graph)
	add_rocs_cpp_test_suite(query)

endif(ROCS_BUILD_MODULE_CONCEPT)

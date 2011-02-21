if(ROCS_BUILD_MODULE_CONCEPT)

	# Module
	add_rocs_cpp_module(concept
		SOURCES Graph.cc
		HEADERS Graph.h
		LINK_MODULES core)

	# Tests
	add_rocs_cpp_test_suite(graph)

endif(ROCS_BUILD_MODULE_CONCEPT)

if(ROCS_BUILD_MODULE_CONCEPT)

	# Module
	add_rocs_cpp_module(concept
		SOURCES Graph.cc Query.cc
		HEADERS Graph.h Query.h
		LINK_MODULES core
		LINK dai)

	# Tests
	add_rocs_cpp_test_suite(graph)

endif(ROCS_BUILD_MODULE_CONCEPT)

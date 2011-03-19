if(ROCS_BUILD_MODULE_ML)

	# Module
	add_rocs_cpp_module(ml
		SOURCES FactorGraph.cc
		HEADERS FactorGraph.h
		LINK ${OPENCV_LIBRARIES})

	# Tests
	add_rocs_cpp_test_suite(test1)

endif(ROCS_BUILD_MODULE_ML)
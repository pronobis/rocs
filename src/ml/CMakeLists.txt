if(ROCS_BUILD_MODULE_ML)

	# Module
	add_rocs_cpp_module(ml
		SOURCES FactorClassSet.cc VariableClassSet.cc FactorClass.cc VariableClass.cc 
                        Variable.cc Factor.cc FactorGraph.cc ChainGraph.cc
		HEADERS FactorClassSet.h VariableClassSet.h FactorClass.h VariableClass.h 
                        Variable.h Factor.h FactorGraph.h ChainGraph.h
		LINK ${OPENCV_LIBRARIES})

	# Tests
	add_rocs_cpp_test_suite(test1)

endif(ROCS_BUILD_MODULE_ML)
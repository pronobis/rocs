if(ROCS_BUILD_MODULE_CORE)

	# Module
	add_rocs_cpp_module(core
		SOURCES Configuration.cc CommandLineHelp.cc
		HEADERS debug.h error.h utils.h types.h Configuration.h Timer.h CommandLineHelp.h  
		LINK ${BOOST_PROGRAM_OPTIONS_LIBRARIES})

	# Tests
	add_rocs_cpp_test_suite(test1)
	add_rocs_cpp_test_suite(configuration)

endif(ROCS_BUILD_MODULE_CORE)
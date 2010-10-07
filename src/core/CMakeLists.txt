if(ROCS_BUILD_MODULE_CORE)

	# Module
	add_rocs_cpp_module(core
		SOURCES Configuration.cc CommandLineHelp.cc ConfigFileReader.cc
		HEADERS debug.h error.h utils.h Configuration.h Timer.h CommandLineHelp.h ConfigFileReader.h Types.h
		LINK ${BOOST_PROGRAM_OPTIONS_LIBRARIES})

	# Tests
	add_rocs_cpp_test_suite(test1)

endif(ROCS_BUILD_MODULE_CORE)
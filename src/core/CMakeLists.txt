if(ROCS_BUILD_MODULE_CORE)

	# Module
	add_rocs_cpp_module(core
		SOURCES CommandLineHelp.cc ConfigFileReader.cc InputMixer.cc
		HEADERS debug.h error.h utils.h InputMixer.h Timer.h CommandLineHelp.h ConfigFileReader.h Types.h
		LINK ${BOOST_PROGRAM_OPTIONS_LIBRARIES})

	# Tests
	add_rocs_cpp_test_suite(test1)

endif(ROCS_BUILD_MODULE_CORE)
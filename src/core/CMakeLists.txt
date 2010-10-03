if(ROCS_BUILD_MODULE_CORE)

	# Module
	add_rocs_cpp_module(core
		SOURCES CommandLineHelp.cc ConfigFileReader.cc Core.cc InputMixer.cc
		HEADERS Core.h Debug.h Error.h InputMixer.h Timer.h CommandLineHelp.h ConfigFileReader.h Types.h
		LINK ${BOOST_PROGRAM_OPTIONS_LIBRARIES})

	# Tests
	add_rocs_cpp_test_suite(test1)

endif(ROCS_BUILD_MODULE_CORE)
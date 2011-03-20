if(ROCS_BUILD_MODULE_CORE)

	# Module
	add_rocs_cpp_module(core
		SOURCES Configuration.cc CommandLineHelp.cc FileInfo.cc
		HEADERS debug.h error.h Configuration.h Timer.h CommandLineHelp.h FileInfo.h ShallowCopyable.h
		LINK ${BOOST_PROGRAM_OPTIONS_LIBRARIES} ${BOOST_FILESYSTEM_LIBRARIES})

	# Tests
	add_rocs_cpp_test_suite(test1)
	add_rocs_cpp_test_suite(configuration)

endif(ROCS_BUILD_MODULE_CORE)
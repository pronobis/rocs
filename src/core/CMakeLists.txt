# Module
add_rocs_cpp_module(core
  SOURCES Config.cc CommandLineHelp.cc FileInfo.cc
  HEADERS debug.h error.h Config.h Timer.h CommandLineHelp.h FileInfo.h
  LINK ${BOOST_PROGRAM_OPTIONS_LIBRARIES} ${BOOST_FILESYSTEM_LIBRARIES})

# Tests
add_rocs_cpp_test(test)
add_rocs_cpp_test(config)


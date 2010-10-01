# C++
## Dependencies
depend_on_boost(1.40.0 COMPONENTS program_options property_tree USEDBY "Module Core")

## Definition of the module
add_rocs_cpp_module(Core 
	SOURCES CommandLineHelp.cc ConfigFileReader.cc Core.cc InputMixer.cc
	HEADERS Core.h Debug.h Error.h InputMixer.h Timer.h CommandLineHelp.h ConfigFileReader.h Types.h
	LINK boost_program_options)


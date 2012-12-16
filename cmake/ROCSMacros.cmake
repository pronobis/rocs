# ===============================================================================
# ROCS - Toolkit for Robots Comprehending Space
# Copyright (c) 2010-2012, the ROCS authors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met: 
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer. 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution. 
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ===============================================================================

# ------------------------------------------------------------------
# ROCSMacros.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# Internal ROCS-specific.
# ------------------------------------------------------------------


# Adds a C++ module
# Arguments: 
# <name> SOURCES <source_file> [<source_file> ...] 
# HEADERS <header_file> [<header_file> ...]
# LINK <library> [<library> ...]
# LINK_MODULES <module> [<module> ...]
macro(add_rocs_cpp_module)
	# Parse arguments
	parse_arguments(ARG "SOURCES;HEADERS;LINK;LINK_MODULES" "" ${ARGN})
	list(GET ARG_DEFAULT_ARGS 0 ARG_NAME)

	# Set a "public" variable MODULE_NAME
	set(MODULE_NAME ${ARG_NAME})

	# Add to list of modules
	set(ROCS_MODULE_LIST ${ARG_NAME} ${ROCS_MODULE_LIST} PARENT_SCOPE)

	# Get sources
	set(_SOURCES_ "")
	foreach(I ${ARG_SOURCES})
		set(_SOURCES_ "cpp/rocs/${ARG_NAME}/${I}" ${_SOURCES_})
	endforeach(I)

	# Get headers
	set(_HEADERS_ "")
	foreach(I ${ARG_HEADERS})
		set(_HEADERS_ "cpp/rocs/${ARG_NAME}/${I}" ${_HEADERS_})
	endforeach(I)

	# Add library
	add_library(rocs_${ARG_NAME} SHARED ${_SOURCES_})

	# Get and add linked libraries
	if(NOT "${ARG_LINK}" STREQUAL "")
		target_link_libraries(rocs_${ARG_NAME} ${ARG_LINK})
	endif(NOT "${ARG_LINK}" STREQUAL "")

	# Get and add linked module libraries
	if(NOT "${ARG_LINK_MODULES}" STREQUAL "")
		foreach(I ${ARG_LINK_MODULES})
			add_dependencies(rocs_${ARG_NAME} rocs_${I})
			target_link_libraries(rocs_${ARG_NAME} rocs_${I})
		endforeach(I)
	endif(NOT "${ARG_LINK_MODULES}" STREQUAL "")

	# Install
	install(TARGETS rocs_${ARG_NAME} LIBRARY DESTINATION ${ROCS_DIR}/lib ARCHIVE DESTINATION lib)
	install(FILES cpp/rocs/${ARG_NAME}.h DESTINATION ${ROCS_DIR}/include/rocs)
	install(FILES ${_HEADERS_} DESTINATION ${ROCS_DIR}/include/rocs/${ARG_NAME})

	# Make the module available to others
	include_directories(cpp)
endmacro(add_rocs_cpp_module)


# Adds a C++ application
# Arguments: 
# <name> SOURCES <source_file> [<source_file> ...] 
# LINK <library> [<library> ...]
# LINK_MODULES <module> [<module> ...]
macro(add_rocs_cpp_app)
	# Parse arguments
	parse_arguments(ARG "SOURCES;HEADERS;LINK;LINK_MODULES" "" ${ARGN})
	list(GET ARG_DEFAULT_ARGS 0 ARG_NAME)

	# Check if module name is set
	if("${MODULE_NAME}" STREQUAL "")
		message(FATAL_ERROR "Module must be defined before a test suite can be defined!")
	endif("${MODULE_NAME}" STREQUAL "") 

	# Get sources
	set(_SOURCES_ "")
	foreach(I ${ARG_SOURCES})
		set(_SOURCES_ "cpp/apps/${I}" ${_SOURCES_})
	endforeach(I)

	# Add executable
	add_executable(rocs_${ARG_NAME} ${_SOURCES_})

	# Get and add linked libraries
	if(NOT "${ARG_LINK}" STREQUAL "")
		target_link_libraries(rocs_${ARG_NAME} ${ARG_LINK})
	endif(NOT "${ARG_LINK}" STREQUAL "")

	# Get and add linked module libraries
	if(NOT "${ARG_LINK_MODULES}" STREQUAL "")
		foreach(I ${ARG_LINK_MODULES})
			add_dependencies(rocs_${ARG_NAME} rocs_${I})
			target_link_libraries(rocs_${ARG_NAME} rocs_${I})
		endforeach(I)
	endif(NOT "${ARG_LINK_MODULES}" STREQUAL "")

	# Install
	install(TARGETS rocs_${ARG_NAME} RUNTIME DESTINATION ${ROCS_DIR}/bin)
endmacro(add_rocs_cpp_app)


# Adds a C++ test application
# Arguments:
# <test_name>
macro(add_rocs_cpp_test)
	# Parse arguments
	parse_arguments(ARG "" "" ${ARGN})
	list(GET ARG_DEFAULT_ARGS 0 ARG_NAME)

	# Check if module name is set
	if("${MODULE_NAME}" STREQUAL "")
		message(FATAL_ERROR "Module must be defined before a test suite can be defined!")
	endif("${MODULE_NAME}" STREQUAL "") 

	# Check if we build tests at all
	if(ROCS_BUILD_TESTS)
		# Full test suite name
		set(_TEST_TARGET_ "test_${MODULE_NAME}_${ARG_NAME}") 

		# Add target for the test
		add_executable(${_TEST_TARGET_} cpp/tests/test_${ARG_NAME}.cc)
                target_link_libraries(${_TEST_TARGET_} pthread gtest gtest_main)
		target_link_libraries(${_TEST_TARGET_} rocs_${MODULE_NAME})

		# Special definitions used by Boost 
		set_property(TARGET ${_TEST_TARGET_} PROPERTY COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK" "BOOST_TEST_MODULE=${_TEST_TARGET_}")   

		# Say where it should be built
		set_target_properties(${_TEST_TARGET_} PROPERTIES
				RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/")

		# Make output of CTest verbose on failure
 		# set(CTEST_OUTPUT_ON_FAILURE true) - doesn't work needs fixing

		# Add the test
		enable_testing()
		get_target_property(LOC ${_TEST_TARGET_} LOCATION)
		add_test(${_TEST_TARGET_} "${LOC}")

	endif(ROCS_BUILD_TESTS)
endmacro(add_rocs_cpp_test)



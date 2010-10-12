cmake_minimum_required(VERSION 2.6)

# Using CCache to speed up compilation of ROCS
if(ROCS_CCACHE)
	set(CMAKE_CXX_COMPILER "ccache")
	set(CMAKE_CXX_COMPILER_ARG1 "g++")
	set(CMAKE_C_COMPILER "ccache")
	set(CMAKE_C_COMPILER_ARG1 "gcc")
endif(ROCS_CCACHE)

# Definition of the project starts here
project(ROCS)

# Define version
set(ROCS_VERSION "0.1")

# When defined, scripts know they are executed from within ROCS source tree.
set(INSIDE_ROCS YES)

# Get ROCS_SRC_ROOT
get_filename_component(ROCS_SRC_ROOT . ABSOLUTE)

# Set the output directory
set(ROCS_DIR_INIT ${ROCS_DIR})
if ("${ROCS_DIR_INIT}" STREQUAL "")
	set(ROCS_DIR_INIT $ENV{ROCS_DIR})
	if ("${ROCS_DIR_INIT}" STREQUAL "")
		set(ROCS_DIR_INIT ${ROCS_SRC_ROOT})
	endif("${ROCS_DIR_INIT}" STREQUAL "")
endif("${ROCS_DIR_INIT}" STREQUAL "")
set(ROCS_DIR ${ROCS_DIR_INIT} CACHE PATH "Path to the directory where ROCS should be installed.")

# Set build type
if (NOT "${ROCS_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE ${ROCS_BUILD_TYPE})
endif (NOT "${ROCS_BUILD_TYPE}" STREQUAL "")

# Make ROCS_DIR available as preprocessor definition
ADD_DEFINITIONS(-DROCS_DIR="${ROCS_DIR}")

# Are we installing to SRC_ROOT?
get_filename_component(TMP_PATH1 ${ROCS_SRC_ROOT} ABSOLUTE)
get_filename_component(TMP_PATH2 ${ROCS_DIR} ABSOLUTE)
string(COMPARE EQUAL ${TMP_PATH1} ${TMP_PATH2} INSTALL_TO_SRC_ROOT)

# Set other paths
set(ROCS_SRC_DOC ${ROCS_SRC_ROOT}/doc)
set(ROCS_SRC_CMAKE ${ROCS_SRC_ROOT}/cmake)
set(ROCS_SRC_CONFIG ${ROCS_SRC_ROOT}/config)
set(ROCS_SRC_DATA ${ROCS_SRC_ROOT}/data)
set(ROCS_SRC_TEST ${ROCS_SRC_ROOT}/test)
set(ROCS_SRC_MODULES ${ROCS_SRC_ROOT}/src)
set(ROCS_SRC_THIRDPARTY ${ROCS_SRC_ROOT}/thirdparty)

# Use cmake files packaged with ROCS
set(CMAKE_MODULE_PATH "${ROCS_SRC_ROOT}/cmake" ${CMAKE_MODULE_PATH} )

# General build configuration
add_definitions(-Wall)

# Includes
## General purpose macros
include(BasicMacros) 
## ROCS-specific macros
include(ROCSMacros) 
# Build options
include(ROCSBuildOpts) 
# Component dependencies
include(ROCSDeps)
# Finding external dependencies
include(ROCSExtDeps)

# Debug level
set(ROCS_DEBUG_LEVEL 0 CACHE PATH "Debug level used by ROCS (0-3).")
ADD_DEFINITIONS(-DROCS_DEBUG_LEVEL=${ROCS_DEBUG_LEVEL})


# ------------------------------------------------------------------
# Subprojects
# ------------------------------------------------------------------

add_subdirectory(${ROCS_SRC_CONFIG})
add_subdirectory(${ROCS_SRC_DATA})
add_subdirectory(${ROCS_SRC_CMAKE})
install(FILES 
	${ROCS_SRC_ROOT}/README.md ${ROCS_SRC_ROOT}/LICENSE.md 
	${ROCS_SRC_ROOT}/INSTALL.md ${ROCS_SRC_ROOT}/CHANGELOG.md 
	DESTINATION ${ROCS_DIR}/doc)

# Thirdparty
add_subdirectory_with_includes(${ROCS_SRC_THIRDPARTY}/boost)
add_subdirectory_with_includes(${ROCS_SRC_THIRDPARTY}/cimg)
add_subdirectory_with_includes(${ROCS_SRC_THIRDPARTY}/libdai)

# Modules
add_subdirectory_with_includes(${ROCS_SRC_MODULES}/core)
add_subdirectory_with_includes(${ROCS_SRC_MODULES}/math)
add_subdirectory_with_includes(${ROCS_SRC_MODULES}/cv)

# Documentation - modules must be already defined
add_subdirectory(${ROCS_SRC_DOC})


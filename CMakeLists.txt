cmake_minimum_required(VERSION 2.8)
include(ExternalProject)

# Message
message(STATUS "================================")
message(STATUS "Configuring ROCS")
message(STATUS "================================")

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
		set(ROCS_DIR_INIT ${ROCS_SRC_ROOT}/output)
	endif("${ROCS_DIR_INIT}" STREQUAL "")
endif("${ROCS_DIR_INIT}" STREQUAL "")
set(ROCS_DIR ${ROCS_DIR_INIT} CACHE PATH "Path to the directory where ROCS should be installed.")

# Set build type
if("${ROCS_BUILD_TYPE}" STREQUAL "")
    set(ROCS_BUILD_TYPE "Debug")
endif("${ROCS_BUILD_TYPE}" STREQUAL "")
set(ROCS_BUILD_TYPE ${ROCS_BUILD_TYPE} CACHE PATH "ROCS build type (Debug/Release).")
set(CMAKE_BUILD_TYPE ${ROCS_BUILD_TYPE} CACHE INTERNAL "" FORCE)

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

# Debug level
if("${ROCS_MAX_DEBUG_LEVEL}" STREQUAL "")
    set(ROCS_MAX_DEBUG_LEVEL 0)
endif("${ROCS_MAX_DEBUG_LEVEL}" STREQUAL "")
set(ROCS_MAX_DEBUG_LEVEL ${ROCS_MAX_DEBUG_LEVEL} CACHE STRING "Maximal debug level compiled into ROCS (0-3).")
add_definitions(-DROCS_MAX_DEBUG_LEVEL=${ROCS_MAX_DEBUG_LEVEL})

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

# Add empty line
message(STATUS "")


# ------------------------------------------------------------------
# Subdirectories
# ------------------------------------------------------------------

add_subdirectory(${ROCS_SRC_CONFIG})
add_subdirectory(${ROCS_SRC_DATA})
add_subdirectory(${ROCS_SRC_CMAKE})
install(FILES 
	${ROCS_SRC_ROOT}/README.md ${ROCS_SRC_ROOT}/LICENSE.md 
	${ROCS_SRC_ROOT}/INSTALL.md ${ROCS_SRC_ROOT}/CHANGELOG.md 
	DESTINATION ${ROCS_DIR}/doc)


# ------------------------------------------------------------------
# Third-party 
# ------------------------------------------------------------------
add_subdirectory_with_includes(${ROCS_SRC_THIRDPARTY}/cimg)

# libdai
if(ROCS_BUILD_THIRDPARTY_LIBDAI)
  add_subdirectory_with_includes(${ROCS_SRC_THIRDPARTY}/libdai)
endif(ROCS_BUILD_THIRDPARTY_LIBDAI)

# Google Test
if(ROCS_BUILD_THIRDPARTY_GTEST)
  externalproject_add(googletest 
    SOURCE_DIR ${ROCS_SRC_THIRDPARTY}/gtest-1.6.0
    # Disable install step
    INSTALL_COMMAND ""
    )
  # Add includes
  externalproject_get_property(googletest source_dir)
  include_directories(${source_dir}/include)  
  externalproject_get_property(googletest binary_dir)
  link_directories(${binary_dir})
endif(ROCS_BUILD_THIRDPARTY_GTEST)


# ------------------------------------------------------------------
# Modules
# ------------------------------------------------------------------
# Core
if(ROCS_BUILD_MODULE_CORE)
  add_subdirectory_with_includes(${ROCS_SRC_MODULES}/core)
endif(ROCS_BUILD_MODULE_CORE)

# Vision
if(ROCS_BUILD_MODULE_VISION)
  add_subdirectory_with_includes(${ROCS_SRC_MODULES}/vision)
endif(ROCS_BUILD_MODULE_VISION)


# ------------------------------------------------------------------
# Documentation 
# Modules must be already defined
# ------------------------------------------------------------------
add_subdirectory(${ROCS_SRC_DOC})


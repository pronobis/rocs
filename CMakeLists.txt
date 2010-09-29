cmake_minimum_required(VERSION 2.8)
project(ROCS)

# Define version
set(ROCS_VERSION "0.1")

# When defined, scripts know they are executed from within ROCS source tree.
set(INSIDE_ROCS YES)

# Get ROCS_SRC_ROOT
get_filename_component(ROCS_SRC_ROOT . ABSOLUTE)

# Set the output directory
set(ROCS_DIR_INIT $ENV{ROCS_DIR})
if ("${ROCS_DIR_INIT}" STREQUAL "")
    set(ROCS_DIR_INIT ${ROCS_SRC_ROOT})
endif ("${ROCS_DIR_INIT}" STREQUAL "")
set(ROCS_DIR ${ROCS_DIR_INIT} CACHE PATH "Path to the directory where ROCS should be installed.")
set(CMAKE_INSTALL_PREFIX "${ROCS_DIR}" CACHE INTERNAL "Prefix prepended to install directories." FORCE)

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

# Include ROCS macros file
include(ROCSMacros)


# ------------------------------------------------------------------
# Subprojects
# ------------------------------------------------------------------

# Obligatory
add_subdirectory(${ROCS_SRC_CONFIG})
add_subdirectory(${ROCS_SRC_DATA})
add_subdirectory(${ROCS_SRC_CMAKE})
add_subdirectory(${ROCS_SRC_MODULES}/Core)

option(BUILD_DOC "Build documentation." YES)
if(BUILD_DOC)
    add_subdirectory(${ROCS_SRC_DOC})
endif(BUILD_DOC)

# Optional
#option(BUILD_MODULE_TOOLS "Build module Tools." YES)
#if(BUILD_MODULE_TOOLS)
#    add_subdirectory(${ROCS_SRC_MODULES}/Tools)
#endif(BUILD_MODULE_TOOLS)

#option(BUILD_APPS "Build applications." YES)
#if(BUILD_APPS)
#    add_subdirectory(${ROCS_SRC_APPS})
#endif(BUILD_APPS)

#option(BUILD_TEST "Build test/demo applications." NO)
#if(BUILD_TEST)
#    add_subdirectory(${ROCS_SRC_TEST})
#endif(BUILD_TEST)



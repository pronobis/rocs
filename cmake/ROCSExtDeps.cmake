# ==================================================================
# ROCS - Toolkit for Robots Comprehending Space
# Copyright (C) 2010  Andrzej Pronobis
#
# This file is part of ROCS.
#
# ROCS is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3
# of the License, or (at your option) any later version.
#
# ROCS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ROCS. If not, see <http://www.gnu.org/licenses/>.
# ==================================================================

# ------------------------------------------------------------------
# ROCSExtDeps.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# Finds the external dependencies.
# ------------------------------------------------------------------

# Message
message(STATUS "")
message(STATUS "================================")
message(STATUS "External Dependencies")
message(STATUS "================================")


if(ROCS_FIND_DOXYGEN)
  find_package(Doxygen)
  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen not found. Documentation cannot be generated.")
  endif (NOT DOXYGEN_FOUND)
  message(STATUS "-> Doxygen found.")
  set(ROCS_FIND_DOXYGEN_STATUS "found")
endif(ROCS_FIND_DOXYGEN)


if(ROCS_FIND_BOOST_HEADERS)
  find_package(Boost 1.40.0)
  if(NOT Boost_FOUND)
    message(FATAL_ERROR " Boost header files version >=1.40.0 not found.")
  endif(NOT Boost_FOUND)
  message(STATUS "-> Boost header files version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}.")
  # Set includes
  include_directories(${Boost_INCLUDE_DIRS})
endif(ROCS_FIND_BOOST_HEADERS)


if(ROCS_FIND_BOOST_PROGRAM_OPTIONS)
  find_package(Boost 1.40.0 COMPONENTS program_options)
  if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost program_options version >=1.40.0 not found.")
  endif(NOT Boost_FOUND)
  message(STATUS "-> Boost program_options version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}.")
  # Set includes/libraries
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
  set(BOOST_PROGRAM_OPTIONS_LIBRARIES ${Boost_LIBRARIES})
endif(ROCS_FIND_BOOST_PROGRAM_OPTIONS)


if(ROCS_FIND_BOOST_SYSTEM)
  find_package(Boost 1.40.0 COMPONENTS system)
  if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost system version >=1.40.0 not found.")
  endif(NOT Boost_FOUND)
  message(STATUS "-> Boost system version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}.")
  # Set includes/libraries
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
  set(BOOST_SYSTEM_LIBRARIES ${Boost_LIBRARIES})
endif(ROCS_FIND_BOOST_SYSTEM)


if(ROCS_FIND_BOOST_FILESYSTEM)
  find_package(Boost 1.40.0 COMPONENTS filesystem)
  if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost filesystem version >=1.40.0 not found.")
  endif(NOT Boost_FOUND)
  message(STATUS "-> Boost filesystem version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}.")
  # Set includes/libraries
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
  set(BOOST_FILESYSTEM_LIBRARIES ${Boost_LIBRARIES})
endif(ROCS_FIND_BOOST_FILESYSTEM)


if(ROCS_FIND_BOOST_UNIT_TEST_FRAMEWORK)
  find_package(Boost 1.40.0 COMPONENTS unit_test_framework)
  if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost unit_test_framework version 1.40.0 not found.")
  endif(NOT Boost_FOUND)
  message(STATUS "-> Boost unit_test_framework version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}.")
  # Set includes/libraries
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
  set(BOOST_UNIT_TEST_FRAMEWORK_LIBRARIES ${Boost_LIBRARIES})
endif(ROCS_FIND_BOOST_UNIT_TEST_FRAMEWORK)

if(ROCS_FIND_OPENCV)
  # Try with pkgconfig first (usually works for Ubuntu repository library) 
  find_package(OpenCVPkgConfig)
  if(OpenCV_FOUND)
    # Found it!
    # Test version
    if(OpenCV_VERSION LESS 2.1)
      message(FATAL_ERROR "OpenCV found, but the version is smaller than 2.1.")
    endif(OpenCV_VERSION LESS 2.1)
    # Set includes/libraries
    include_directories(${OpenCV_INCLUDE_DIRS}/.. ${OpenCV_INCLUDE_DIRS})
    link_directories(${OpenCV_LIBRARY_DIRS})
    set(OPENCV_LIBRARIES ${OpenCV_LIBRARIES})
  else(OpenCV_FOUND)
    ########## THIS PART OF THE CODE IS NOT YET TESTED AND IS LIKELY TO CONTAIN BUGS ###########
    # Not found, try searching in various paths
    set(OpenCV_FIND_QUIETLY YES)
    find_package(OpenCV)
    if(NOT OpenCV_FOUND)
      message(FATAL_ERROR "OpenCV not found!")
    endif(NOT OpenCV_FOUND)
    # Test version
    if(OpenCV_VERSION LESS 2)
      message(FATAL_ERROR "OpenCV found, but the version is smaller than 2.0.")
    endif(OpenCV_VERSION LESS 2)
    # Set includes/libraries
    include_directories(${OpenCV_INCLUDE_DIR})
    set(OPENCV_LIBRARIES ${OpenCV_LIBS})
  endif(OpenCV_FOUND)
  message(STATUS "-> OpenCV version ${OpenCV_VERSION}.")
endif(ROCS_FIND_OPENCV)


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

if(ROCS_FIND_DOXYGEN)
	find_package(Doxygen)
	if (NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen not found. Documentation cannot be generated.")
	endif (NOT DOXYGEN_FOUND)
	message(STATUS "Found Doxygen.")
endif(ROCS_FIND_DOXYGEN)

if(ROCS_FIND_BOOST_PROPERTY_TREE)
	find_package(Boost 1.41.0 COMPONENTS property_tree)
	if(NOT Boost_FOUND)
		message(STATUS "The system Boost property_tree library version 1.41.0 not found. Using the internal Boost property_tree library.")
		set(ROCS_BUILD_THIRDPARTY_BOOST_PROPERTY_TREE YES)
	else(NOT Boost_FOUND)
		message(STATUS "Found the system Boost property_tree library version ${Boost_VERSION}.")
		# Set includes/libraries
		include_directories(${Boost_INCLUDE_DIRS})
		link_directories(${Boost_LIBRARY_DIRS})
		set(BOOST_PROPERTY_TREE_LIBRARY ${Boost_LIBRARIES})
	endif(NOT Boost_FOUND)
endif(ROCS_FIND_BOOST_PROPERTY_TREE)


if(ROCS_FIND_BOOST_PROGRAM_OPTIONS)
	find_package(Boost 1.40.0 COMPONENTS program_options)
	if(NOT Boost_FOUND)
		message(FATAL_ERROR "The system Boost program_options library version 1.40.0 not found.")
	endif(NOT Boost_FOUND)
	message(STATUS "Found the system Boost program_options library version ${Boost_VERSION}.")
	# Set includes/libraries
	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})
	set(BOOST_PROGRAM_OPTIONS_LIBRARY ${Boost_LIBRARIES})
endif(ROCS_FIND_BOOST_PROGRAM_OPTIONS)


if(ROCS_FIND_OPENCV)
	find_package(OpenCV)
	if(NOT OpenCV_FOUND)
		message(FATAL_ERROR "OpenCV library not found.")
	endif(NOT OPENCV_FOUND)
	if(OpenCV_VERSION_MAJOR LESS 2)
		message(FATAL_ERROR "OpenCV library found, but the version is smaller than 2.0.")
	endif(OpenCV_VERSION_MAJOR LESS 2)
	message(STATUS "Found OpenCV library version ${OpenCV_VERSION}.")
	# Set includes/libraries
	include_directories(${OPENCV_INCLUDE_DIR})
	## OPENCV_LIBRARIES defined by find_packages
endif(ROCS_FIND_OPENCV)


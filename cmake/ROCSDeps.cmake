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
# ROCSDeps.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# Macros used to declare dependencies.
# ------------------------------------------------------------------

# Declares dependency on Boost
# Arguments:
# <version> COMPONENTS <components> USEDBY <what_uses_them>
macro(depend_on_boost)
	# Parse arguments
	parse_arguments(ARG "COMPONENTS;USEDBY" "" ${ARGN})
	list(GET ARG_DEFAULT_ARGS 0 ARG_VERSION)

	# Test if we use the internal boost components
	if(ROCS_USE_INTERNAL_BOOST)
		# Use the components that we have internally
		## property_tree
		list(FIND ARG_COMPONENTS "property_tree" TMP) 
		if(${TMP})
			list(REMOVE_ITEM ARG_COMPONENTS "property_tree")
			message(STATUS "Using internal Boost property_tree library (required by the ${ARG_USEDBY}).")
			include_directories(${ROCS_SRC_THIRDPARTY}/boost)
		endif(${TMP})
	endif(ROCS_USE_INTERNAL_BOOST)

	# Check if the (remaining) components exist in the system
	separate_by_spaces(COMPONENTS_SEPARATED ARG_COMPONENTS)
	find_package(Boost ${ARG_VERSION} COMPONENTS ${COMPONENTS_SEPARATED})
	if(NOT Boost_FOUND)
		message(FATAL_ERROR "System Boost libraries (${COMPONENTS_SEPARATED}) version ${ARG_VERSION} not found. Those libraries are required by the ${ARG_USEDBY}. Try enabling ROCS_USE_INTERNAL_BOOST.")
	endif(NOT Boost_FOUND)
	message(STATUS "Using system Boost libraries (${COMPONENTS_SEPARATED}) version ${Boost_VERSION} (required by ${ARG_USEDBY}).")

	# Set directories
	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})
endmacro(depend_on_boost)


# Declares dependency on OpenCV
# Arguments:
# USEDBY <what_uses_them>
macro(depend_on_opencv)
	# Parse arguments
	parse_arguments(ARG "USEDBY" "" ${ARGN})
	
	# Find system OpenCV
	find_package(OpenCV)
	if(NOT OpenCV_FOUND)
		message(FATAL_ERROR "OpenCV library not found. OpenCV 2.x is required by the ${ARG_USEDBY}.")
	endif(NOT OPENCV_FOUND)
	if(OpenCV_VERSION_MAJOR LESS 2)
		message(FATAL_ERROR "OpenCV library found, but the version is not 2.x. OpenCV 2.x is are required by the ${ARG_USEDBY}.")
	endif(OpenCV_VERSION_MAJOR LESS 2)
	message(STATUS "Using OpenCV library version ${OpenCV_VERSION} (required by ${ARG_USEDBY}).")

	# Set directories
	include_directories(${OPENCV_INCLUDE_DIR})
endmacro(depend_on_opencv)


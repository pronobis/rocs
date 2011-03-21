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
# ROCSBuildOpts.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# Defines build options.
# Use it to set the build variables for the components
# that directly result from the requested functionality.
# Dependencies are resolved elsewhere.
#
# Set ROCS_DONT_DEFINE_OPTIONS if you don't want the options
# to be defined. This is useful when ROCS is included into
# a larger project.
# ------------------------------------------------------------------

if(NOT ROCS_DONT_DEFINE_OPTIONS)
	# Documentation
	if("${ROCS_BUILD_DOC}" STREQUAL "")
		set(ROCS_BUILD_DOC NO)
	endif("${ROCS_BUILD_DOC}" STREQUAL "")
	option(ROCS_BUILD_DOC "Build documentation." ${ROCS_BUILD_DOC})
	# Tests
	if("${ROCS_BUILD_TESTS}" STREQUAL "")
		set(ROCS_BUILD_TESTS YES)
	endif("${ROCS_BUILD_TESTS}" STREQUAL "")
	option(ROCS_BUILD_TESTS "Build tests." ${ROCS_BUILD_TESTS})
	# GPL 3rd-party components
	if("${ROCS_BUILD_GPL}" STREQUAL "")
		set(ROCS_BUILD_GPL YES)
	endif("${ROCS_BUILD_GPL}" STREQUAL "")
	option(ROCS_BUILD_GPL "Should ROCS be compiled with GPL components?" ${ROCS_BUILD_GPL})
	add_definitions(-DROCS_BUILD_GPL=${ROCS_BUILD_GPL})
	# Build Qt GUI
	if("${ROCS_BUILD_QTGUI}" STREQUAL "")
		set(ROCS_BUILD_QTGUI YES)
	endif("${ROCS_BUILD_QTGUI}" STREQUAL "")
	option(ROCS_BUILD_QTGUI "Build components depending on Qt GUI." ${ROCS_BUILD_QTGUI})
	add_definitions(-DROCS_BUILD_QTGUI=${ROCS_BUILD_QTGUI})
	# Core
	option(USE_MODULE_CORE "Use the module Core." NO)
	if(USE_MODULE_CORE)
		set(ROCS_BUILD_MODULE_CORE YES)
	endif(USE_MODULE_CORE)
	# Math
	option(USE_MODULE_MATH "Use the module Math." NO)
	if(USE_MODULE_MATH)
		set(ROCS_BUILD_MODULE_MATH YES)
	endif(USE_MODULE_MATH)
	# Ml
	option(USE_MODULE_ML "Use the module Ml." NO)
	if(USE_MODULE_ML)
		set(ROCS_BUILD_MODULE_ML YES)
	endif(USE_MODULE_ML)
	# Vision
	option(USE_MODULE_VISION "Use the module Vision." NO)
	if(USE_MODULE_VISION)
		set(ROCS_BUILD_MODULE_VISION YES)
	endif(USE_MODULE_VISION)
	# CV Apps
	option(USE_MODULE_VISION_APPS "Use applications of the module CV." NO)
	if(USE_MODULE_VISION_APPS)
		set(ROCS_BUILD_MODULE_VISION_APPS YES)
	endif(USE_MODULE_VISION_APPS)
	# Concept
	option(USE_MODULE_CONCEPT "Use the module Concept." NO)
	if(USE_MODULE_CONCEPT)
		set(ROCS_BUILD_MODULE_CONCEPT YES)
	endif(USE_MODULE_CONCEPT)
endif(NOT ROCS_DONT_DEFINE_OPTIONS)


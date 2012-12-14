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
  
  # Core
  option(USE_MODULE_CORE "Use the module Core." NO)
  if(USE_MODULE_CORE)
    set(ROCS_BUILD_MODULE_CORE YES)
  endif(USE_MODULE_CORE)
  
  # Vision
  option(USE_MODULE_VISION "Use the module Vision." NO)
  if(USE_MODULE_VISION)
    set(ROCS_BUILD_MODULE_VISION YES)
  endif(USE_MODULE_VISION)
  
  # Vision Apps
  option(USE_MODULE_VISION_APPS "Use applications of the module CV." NO)
  if(USE_MODULE_VISION_APPS)
    set(ROCS_BUILD_MODULE_VISION_APPS YES)
  endif(USE_MODULE_VISION_APPS)

endif(NOT ROCS_DONT_DEFINE_OPTIONS)


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


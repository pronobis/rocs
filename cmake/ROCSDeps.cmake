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
# ROCSDeps.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# Defines component dependencies. 
# Use it to define direct dependencies of every component or app.
# ------------------------------------------------------------------

# Module Concept
# if(ROCS_BUILD_MODULE_CONCEPT)
# 	set(ROCS_BUILD_MODULE_CONCEPT yes)
# 	set(ROCS_BUILD_MODULE_ML yes)
# 	set(ROCS_BUILD_MODULE_CORE yes)
# 	set(ROCS_BUILD_THIRDPARTY_LIBDAI yes)
# 	set(ROCS_FIND_OPENCV yes)
# endif(ROCS_BUILD_MODULE_CONCEPT)

# Module Vision Apps
if(ROCS_BUILD_MODULE_VISION_APPS)
  set(ROCS_BUILD_MODULE_VISION yes)
endif(ROCS_BUILD_MODULE_VISION_APPS)

# Module Vision
if(ROCS_BUILD_MODULE_VISION)
  set(ROCS_BUILD_MODULE_CORE yes)
  set(ROCS_FIND_OPENCV yes)
endif(ROCS_BUILD_MODULE_VISION)

# # Module Ml
# if(ROCS_BUILD_MODULE_ML)
# 	set(ROCS_BUILD_MODULE_CORE yes)
# 	set(ROCS_BUILD_MODULE_MATH yes)
# 	set(ROCS_FIND_OPENCV yes)
# endif(ROCS_BUILD_MODULE_ML)

# Module Math
# if(ROCS_BUILD_MODULE_MATH)
# 	set(ROCS_BUILD_MODULE_CORE yes)
# 	set(ROCS_FIND_OPENCV yes)
# endif(ROCS_BUILD_MODULE_MATH)

# Module Core
if(ROCS_BUILD_MODULE_CORE)
  set(ROCS_FIND_BOOST_PROGRAM_OPTIONS yes)
  set(ROCS_FIND_BOOST_SYSTEM yes)
  set(ROCS_FIND_BOOST_FILESYSTEM yes)
  set(ROCS_FIND_BOOST_HEADERS yes)
endif(ROCS_BUILD_MODULE_CORE)

# Documentation
if(ROCS_BUILD_DOC)
  set(ROCS_FIND_DOXYGEN yes)
endif(ROCS_BUILD_DOC)

# Testing
if(ROCS_BUILD_TESTS)
  #set(ROCS_FIND_BOOST_UNIT_TEST_FRAMEWORK yes) # Use this for Boost test framework
  set(ROCS_BUILD_THIRDPARTY_GTEST yes)
  enable_testing()
endif(ROCS_BUILD_TESTS)

# Summarize the elements to be built
message(STATUS "Selected components:")
if(ROCS_BUILD_THIRDPARTY_GTEST)
  message(STATUS "-> Google Test Framework") 
endif(ROCS_BUILD_THIRDPARTY_GTEST)
if(ROCS_BUILD_MODULE_CORE)
  message(STATUS "-> Module Core") 
  message(STATUS "   - library") 
  if (ROCS_BUILD_MODULE_CORE_APPS)
    message(STATUS "   - apps") 
  endif (ROCS_BUILD_MODULE_CORE_APPS)
  if (ROCS_BUILD_TESTS)
    message(STATUS "   - tests") 
  endif (ROCS_BUILD_TESTS)
endif(ROCS_BUILD_MODULE_CORE)
if(ROCS_BUILD_MODULE_VISION)
  message(STATUS "-> Module Vision") 
  message(STATUS "   - library") 
  if (ROCS_BUILD_MODULE_VISION_APPS)
    message(STATUS "   - apps") 
  endif (ROCS_BUILD_MODULE_VISION_APPS)
  if (ROCS_BUILD_TESTS)
    message(STATUS "   - tests") 
  endif (ROCS_BUILD_TESTS)
endif(ROCS_BUILD_MODULE_VISION)


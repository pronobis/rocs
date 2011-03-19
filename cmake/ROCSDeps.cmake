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
# Defines component dependencies. 
# Use it to define direct dependencies of every component or app.
# ------------------------------------------------------------------

# Module Concept
if(ROCS_BUILD_MODULE_CONCEPT)
	set(ROCS_BUILD_MODULE_CONCEPT yes)
	set(ROCS_BUILD_MODULE_CORE yes)
	set(ROCS_BUILD_THIRDPARTY_LIBDAI yes)
endif(ROCS_BUILD_MODULE_CONCEPT)

# Module CV Apps
if(ROCS_BUILD_MODULE_CV_APPS)
	set(ROCS_BUILD_MODULE_CV yes)
endif(ROCS_BUILD_MODULE_CV_APPS)

# Module CV
if(ROCS_BUILD_MODULE_CV)
	set(ROCS_BUILD_MODULE_CORE yes)
	set(ROCS_BUILD_MODULE_MATH yes)
	set(ROCS_FIND_OPENCV yes)
endif(ROCS_BUILD_MODULE_CV)

# Module Math
if(ROCS_BUILD_MODULE_MATH)
	set(ROCS_BUILD_MODULE_CORE yes)
	set(ROCS_FIND_OPENCV yes)
endif(ROCS_BUILD_MODULE_MATH)

# Module Core
if(ROCS_BUILD_MODULE_CORE)
	set(ROCS_FIND_BOOST_PROGRAM_OPTIONS yes)
	set(ROCS_FIND_BOOST_PROPERTY_TREE yes)
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
	set(ROCS_FIND_BOOST_UNIT_TEST_FRAMEWORK yes)
	enable_testing()
endif(ROCS_BUILD_TESTS)



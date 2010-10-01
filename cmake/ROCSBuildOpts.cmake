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
# ROCS build options and component interdependency map.
# ------------------------------------------------------------------

# Options
## Documentation
option(ROCS_BUILD_DOC "Build documentation." YES)
## Thirdparty
option(ROCS_USE_INTERNAL_BOOST "Use the available internal Boost libraries." YES)
## Components
option(ROCS_USE_MODULE_CORE "Use the module Core." YES)
option(ROCS_USE_MODULE_MATH "Use the module Math." YES)
option(ROCS_USE_MODULE_CV "Use the module CV." YES)

# Dependencies
if(ROCS_USE_INTERNAL_BOOST)
	set(ROCS_BUILD_THIRDPARTY_BOOST YES)
endif(ROCS_USE_INTERNAL_BOOST)
if(ROCS_USE_MODULE_CORE)
	set(ROCS_BUILD_MODULE_CORE YES)
endif(ROCS_USE_MODULE_CORE)
if(ROCS_USE_MODULE_MATH)
	set(ROCS_BUILD_MODULE_CORE YES)
	set(ROCS_BUILD_MODULE_MATH YES)
endif(ROCS_USE_MODULE_MATH)
if(ROCS_USE_MODULE_CV)
	set(ROCS_BUILD_MODULE_CORE YES)
	set(ROCS_BUILD_MODULE_MATH YES)
	set(ROCS_BUILD_MODULE_CV YES)
endif(ROCS_USE_MODULE_CV)


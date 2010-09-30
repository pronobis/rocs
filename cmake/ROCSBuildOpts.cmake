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

# Mendatory components
set(ROCS_BUILD_MODULE_CORE YES)

# Options
## Documentation
option(ROCS_BUILD_DOC "Build documentation." YES)
## Thirdparty
option(ROCS_USE_INTERNAL_BOOST "Use the available internal Boost libraries." NO)
## Components

# Dependencies
if(ROCS_USE_INTERNAL_BOOST)
	set(ROCS_BUILD_THIRDPARTY_BOOST YES)
endif(ROCS_USE_INTERNAL_BOOST)




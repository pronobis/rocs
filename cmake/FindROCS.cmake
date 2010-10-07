# @WARNING@
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
# FindRocs.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# This module searches for ROCS in the directory pointed to by the
# ROCS_DIR environment variable and then in several standard
# locations.
#
# Sets the following variables:
# ROCS_FOUND - When false, ROCS could not be found.
# ROCS_DIR - Path to the directory where ROCS is installed.
# ROCS_LIBRARY_DIR
# ROCS_INCLUDE_DIR
# ------------------------------------------------------------------


# Check if this script is executed from within ROCS source tree.
if(NOT INSIDE_ROCS)
	find_path(ROCS_DIR
		NAMES include/rocs/core/error.h
		PATHS $ENV{ROCS_DIR}
			/opt/rocs
			/usr/local/rocs
			/opt/local/rocs
			/usr
			/usr/local
			/opt
			/opt/local
  		DOC "Path to the ROCS installation directory.")

	if(ROCS_DIR)
		set(ROCS_FOUND "YES")
		set(ROCS_LIBRARY_DIR ${ROCS_DIR}/lib)
		set(ROCS_INCLUDE_DIR ${ROCS_DIR}/include)
	else(ROCS_DIR)
  		message("The ROCS installation directory was not found.")
                message("Try to set the ROCS_DIR environment variable.")
  		set(ROCS_DIR "" CACHE PATH "Path to the ROCS installation directory." )
	endif(ROCS_DIR)
else(NOT INSIDE_ROCS)
	set(ROCS_FOUND "YES")
endif(NOT INSIDE_ROCS)



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
# FindRocs
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# This module searches for ROCS in the directory pointed to by the
# ROCS_DIR environment variable and then in several standard
# locations.
#
# Sets the following variables:
# ROCS_FOUND - When false, ROCS could not be found.
# ROCS_DIR - Path to the directory where ROCS is installed.
# ------------------------------------------------------------------


# Check if this script is executed from within ROCS source tree.
if(NOT INSIDE_ROCS)
	find_path(ROCS_DIR
		NAMES include/RCore/global.h
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
	else(ROCS_DIR)
  		message("The ROCS installation directory was not found.")
                message("Try to set the ROCS_DIR environment variable.")
  		set(ROCS_DIR "" CACHE PATH "Path to the ROCS installation directory." )
	endif(ROCS_DIR)

	# Replacement for the macro in ROCSMacros.cmake when not built inside ROCS
	macro(add_rocs_cpp_test_app _NAME_ _SOURCES_VAR_)
		# Get sources
		set(_SOURCES_ "")
		foreach(I ${${_SOURCES_VAR_}})
			set(_SOURCES_ "${I}" ${_SOURCES_})
		endforeach(I)

		# Add target
		add_executable(${_NAME_} ${_SOURCES_})

		# Install
		install(TARGETS ${_NAME_} RUNTIME DESTINATION .)
	endmacro(add_rocs_cpp_test_app)
else(NOT INSIDE_ROCS)
	set(ROCS_FOUND "YES")
endif(NOT INSIDE_ROCS)



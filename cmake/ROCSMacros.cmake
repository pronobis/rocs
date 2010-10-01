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
# ROCSMacros.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# Internal ROCS-specific.
# ------------------------------------------------------------------


# Adds a C++ module
# Arguments: 
# <name> SOURCES <source_file> [<source_file> ...] 
# HEADERS <header_file> [<header_file> ...]
# LINK <library> [<library> ...]
macro(add_rocs_cpp_module)
	# Parse arguments
	parse_arguments(ARG "SOURCES;HEADERS;LINK" "" ${ARGN})
	list(GET ARG_DEFAULT_ARGS 0 ARG_NAME)

	# Add to list of modules
	set(ROCS_MODULE_LIST ${ARG_NAME} ${ROCS_MODULE_LIST} PARENT_SCOPE)

	# Get sources
	set(_SOURCES_ "")
	foreach(I IN LISTS ARG_SOURCES)
		set(_SOURCES_ "cpp/rocs/${ARG_NAME}/${I}" ${_SOURCES_})
	endforeach(I)

	# Get headers
	set(_HEADERS_ "")
	foreach(I IN LISTS ARG_HEADERS)
		set(_HEADERS_ "cpp/rocs/${ARG_NAME}/${I}" ${_HEADERS_})
	endforeach(I)

	# Add library
	add_library(rocs_${ARG_NAME} SHARED ${_SOURCES_})

	# Get and add linked libraries
	if(NOT "${ARG_LINK}" STREQUAL "")
		separate_by_spaces(_LIBRARIES_ ARG_LINK)
		target_link_libraries(rocs_${ARG_NAME} ${_LIBRARIES_})
	endif(NOT "${ARG_LINK}" STREQUAL "")
	
	# Install
	install(TARGETS rocs_${ARG_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
	install(FILES ${_HEADERS_} DESTINATION include/rocs/${ARG_NAME})
endmacro(add_rocs_cpp_module)


# Adds a C++ application
macro(add_rocs_cpp_app _NAME_ _SOURCES_VAR_)
	# Get sources
	set(_SOURCES_ "")
	foreach(I ${${_SOURCES_VAR_}})
		set(_SOURCES_ "${I}" ${_SOURCES_})
	endforeach(I)

	# Add target
	add_executable(${_NAME_} ${_SOURCES_})

	# Install
	install(TARGETS ${_NAME_} RUNTIME DESTINATION bin)
endmacro(add_rocs_cpp_app)


# Adds a C++ test application
macro(add_rocs_cpp_test_app _NAME_ _SOURCES_VAR_)
	# Get sources
	set(_SOURCES_ "")
	foreach(I ${${_SOURCES_VAR_}})
		set(_SOURCES_ "${I}" ${_SOURCES_})
	endforeach(I)

	# Add target
	add_executable(${_NAME_} ${_SOURCES_})

	# Install
	install(TARGETS ${_NAME_} RUNTIME DESTINATION test/cpp/${_NAME_})
	if (NOT ${INSTALL_TO_SRC_ROOT})
		install(DIRECTORY ${ROCS_SRC_TEST}/cpp/${_NAME_}/ DESTINATION test/cpp/${_NAME_})
	endif (NOT ${INSTALL_TO_SRC_ROOT})
endmacro(add_rocs_cpp_test_app)



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

# Adds a C++ module
macro(add_rocs_cpp_module _NAME_ _SOURCES_VAR_ _HEADERS_VAR_)
	# Add to list of modules
	set(ROCS_MODULE_LIST ${_NAME_} ${ROCS_MODULE_LIST} PARENT_SCOPE)

	# Get sources
	set(_SOURCES_ "")
	foreach(I ${${_SOURCES_VAR_}})
		set(_SOURCES_ "cpp/${_NAME_}/${I}" ${_SOURCES_})
	endforeach(I)

	# Get headers
	set(_HEADERS_ "")
	foreach(I ${${_HEADERS_VAR_}})
		set(_HEADERS_ "cpp/${_NAME_}/${I}" ${_HEADERS_})
	endforeach(I)

	# Add library
	add_library(Rocs${_NAME_} SHARED ${_SOURCES_})

	# Install
	install(TARGETS Rocs${_NAME_} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
	install(FILES ${_HEADERS_} DESTINATION include/${_NAME_})
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



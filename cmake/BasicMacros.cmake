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
# BasicMacros.cmake
# Author: Andrzej Pronobis <a.pronobis@gmail.com>
#
# Basic internal macros that are not specific to ROCS.
# ------------------------------------------------------------------

# Taken from: http://www.itk.org/Wiki/CMakeMacroParseArguments
# See the link for documentation.
MACRO(PARSE_ARGUMENTS prefix arg_names option_names)
  SET(DEFAULT_ARGS)
  FOREACH(arg_name ${arg_names})    
    SET(${prefix}_${arg_name})
  ENDFOREACH(arg_name)
  FOREACH(option ${option_names})
    SET(${prefix}_${option} FALSE)
  ENDFOREACH(option)

  SET(current_arg_name DEFAULT_ARGS)
  SET(current_arg_list)
  FOREACH(arg ${ARGN})            
    SET(larg_names ${arg_names})    
    LIST(FIND larg_names "${arg}" is_arg_name)                   
    IF (is_arg_name GREATER -1)
      SET(${prefix}_${current_arg_name} ${current_arg_list})
      SET(current_arg_name ${arg})
      SET(current_arg_list)
    ELSE (is_arg_name GREATER -1)
      SET(loption_names ${option_names})    
      LIST(FIND loption_names "${arg}" is_option)            
      IF (is_option GREATER -1)
	     SET(${prefix}_${arg} TRUE)
      ELSE (is_option GREATER -1)
	     SET(current_arg_list ${current_arg_list} ${arg})
      ENDIF (is_option GREATER -1)
    ENDIF (is_arg_name GREATER -1)
  ENDFOREACH(arg)
  SET(${prefix}_${current_arg_name} ${current_arg_list})
ENDMACRO(PARSE_ARGUMENTS)


# Generates a string containing space separated elements of a list
macro(separate_by_spaces _VAR_ _LIST_)
	list(GET ${_LIST_} 0 LIST_START)
	set(LIST_REST ${${_LIST_}})
	list(REMOVE_AT LIST_REST 0)
	set(${_VAR_} "${LIST_START}")
	foreach(I IN LISTS LIST_REST)
		set(${_VAR_} "${${_VAR_}} ${I}")
	endforeach(I)
endmacro(separate_by_spaces)


# Adds a subdirectory, then pulls its include_directories and sets
# them in the current directory scope.
macro(add_subdirectory_with_includes _DIR_NAME_)
	add_subdirectory(${_DIR_NAME_})
	get_directory_property(TMP DIRECTORY ${_DIR_NAME_} INCLUDE_DIRECTORIES)
	include_directories(${TMP})	
endmacro(add_subdirectory_with_includes)
 

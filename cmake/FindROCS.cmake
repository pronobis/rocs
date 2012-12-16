# @WARNING@
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



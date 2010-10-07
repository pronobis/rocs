// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2010  Arnaud Ramey, Andrzej Pronobis
//
// This file is part of ROCS.
//
// ROCS is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3
// of the License, or (at your option) any later version.
//
// ROCS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ROCS. If not, see <http://www.gnu.org/licenses/>.
// ==================================================================

/*!
 * Here we define the macros that print out debug messages when
 * DEBUG_LEVEL is > 0.
 * \author Arnaud Ramey, Andrzej Pronobis
 * \file utils.h
 */

#ifndef _ROCS_CORE_DEBUG_H_
#define _ROCS_CORE_DEBUG_H_

// Std
#include <stdio.h> // for fprintf


namespace rocs {
namespace core {

// Debug level
#ifndef DEBUG_LEVEL
	#define DEBUG_LEVEL 0
#endif

/*! Stringified __LINE__ */
#define DEBUG_STRINGIFY(x) #x
#define __DEBUG_LINE_STR__ DEBUG_STRINGIFY(__LINE__)

/*!
 * The primitive macro for debugging.
 * Accepts message in the printf like fashion.
 */
#define DEBUG(...) \
	printf("[" __FILE__ ":" __DEBUG_LINE_STR__ "] " __VA_ARGS__); \
	printf("\n");

/*!
 * Debugging macro including debug level. Prints out
 * debug messages when DEBUG_LEVEL is > 0.
 */
#define debug( level, ... ) \
	if ( DEBUG_LEVEL >= level ) DEBUG(__VA_ARGS__)

/*!
 *  Define debug() for each level of verbosity.
 *  Accepts message in the printf like fashion.
 */
#define debug1(...)    debug(1, __VA_ARGS__)
#define debug2(...)    debug(2, __VA_ARGS__)
#define debug3(...)    debug(3, __VA_ARGS__)


} // namespace core
} // namespace rocs


#endif /* DEBUG_H_ */

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
 * ROCS_DEBUG_LEVEL is > 0.
 *
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
#ifndef ROCS_DEBUG_LEVEL
	#define ROCS_DEBUG_LEVEL 0
#endif

/*! Stringified __LINE__ */
#define ROCS_DEBUG_STRINGIFY(x) #x
#define ROCS_DEBUG_TO_STRING(x) ROCS_DEBUG_STRINGIFY(x)

/*!
 * The primitive macro for debugging.
 * Accepts message in the printf like fashion.
 */
#define ROCS_DEBUG(...) { \
	printf("[" __FILE__ ":" ROCS_DEBUG_TO_STRING(__LINE__) "] " __VA_ARGS__); \
	printf("\n"); \
}

/*!
 * Debugging macro including debug level. Prints out
 * debug messages when ROCS_DEBUG_LEVEL is > 0.
 */
#define rocsDebug( level, ... ) { \
	if ( ROCS_DEBUG_LEVEL >= level ) ROCS_DEBUG(__VA_ARGS__) \
}

/*!
 *  Define debug() for each level of verbosity.
 *  Accepts message in the printf like fashion.
 */
#define rocsDebug1(...)    rocsDebug(1, __VA_ARGS__)
#define rocsDebug2(...)    rocsDebug(2, __VA_ARGS__)
#define rocsDebug3(...)    rocsDebug(3, __VA_ARGS__)


} // namespace core
} // namespace rocs


#endif /* _ROCS_CORE_DEBUG_H_ */

// ===============================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (c) 2010-2012, the ROCS authors. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met: 
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution. 
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ===============================================================================

/*!
 * Here we define the macros that print out debug messages when
 * ROCS_MAX_DEBUG_LEVEL is > 0.
 *
 * \author Andrzej Pronobis, Arnaud Ramey
 * \file debug.h
 */

#ifndef _ROCS_CORE_DEBUG_H_
#define _ROCS_CORE_DEBUG_H_

// Std
#include <stdio.h> // for fprintf


namespace rocs {
namespace core {

// Debug level
#ifndef ROCS_MAX_DEBUG_LEVEL
  #define ROCS_MAX_DEBUG_LEVEL 0
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
 * debug messages when ROCS_MAX_DEBUG_LEVEL is > 0.
 */
#define rocsDebug( level, ... ) { \
	if ( ROCS_MAX_DEBUG_LEVEL >= level ) ROCS_DEBUG(__VA_ARGS__) \
}

/*!
 *  Define debug for each level of verbosity.
 *  Accepts message in the printf like fashion.
 */
#define rocsDebug1(...)    rocsDebug(1, __VA_ARGS__)
#define rocsDebug2(...)    rocsDebug(2, __VA_ARGS__)
#define rocsDebug3(...)    rocsDebug(3, __VA_ARGS__)


} // namespace core
} // namespace rocs


#endif /* _ROCS_CORE_DEBUG_H_ */
